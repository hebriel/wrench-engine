//
// @authors {underdisk}
// License : LGPLv3
//

#include <window/window.h>
#include <renderer/gl/all.h>
#include <renderer/common/renderer.h>
#include <renderer/gl/gl_renderer.h>
#include <renderer/common/camera.h>
#include <renderer/common/render_states.h>

int main()
{
	//Initialize the engine
	wrench::init();

	//OpenGL configuration
	wrench::gl::GLSettings settings;
	settings.useDoubleBuffering = true;
	settings.useCore = true;
	settings.majorVersion = 4; //OpenGL 4.1
	settings.minorVersion = 1;

	//Create the window and attach an OpenGL context to it
	wrench::Window window({800, 600}, "Wrench : Example");
	window.initContext<wrench::gl::GLContext>(settings);

	window.set_framerate_limit(10000);

	auto renderer = wrench::Renderer::create<wrench::gl::GLRenderer>(window);

	//Create a shader
	wrench::gl::GLShader shader;

	//Search the shader files, compiling them, and linking them
	shader
		.add_vertex_shader_by_file("resources/shader.vert")
		.add_fragment_shader_by_file("resources/shader.frag")
		.link();

	//Here are our vertices for our Vertex Buffer Object
	float vertices[] = {
		//Position				//Color
		-1.0f, -1.0f, 0.0f, 	1, 0, 0, 1,
		 1.0f, -1.0f, 0.0f, 	0, 1, 0, 1,
		 1.0f,  1.0f, 0.0f, 	0, 0, 1, 1,
		-1.0f,  1.0f, 0.0f, 	1, 0, 1, 1,
	};

	//Here are our indices for our Vertex Buffer Object
	unsigned indices[6] = {
			0, 1, 2,
			2, 3, 0
	};

	//Create the layout, made of a Vec3 (position) and a Vec4 (color)
	wrench::Layout layout = {
			{wrench::DataType::Vec3, "a_Position"},
			{wrench::DataType::Vec4, "a_Color"},
	};

	//Create our Vertex Buffer Object and attach the layout to it
	auto VBO = wrench::VertexBuffer::create<wrench::gl::GLVertexBuffer>((float*)vertices, sizeof(vertices));
	VBO->bind();
	VBO->setLayout(layout);

	//Create our Index Buffer
	auto EBO = wrench::IndexBuffer::create<wrench::gl::GLIndexBuffer>(indices, sizeof(indices));
	EBO->bind();

	//Create our Vertex Array and attach the Vertex Buffer Object and the Index Buffer
	auto VAO = wrench::VertexArray::create<wrench::gl::GLVertexArray>();
	VAO->add_vertex_buffer(VBO);
	VAO->set_index_buffer(EBO);

	//Set the nice orange background color
	renderer->change_clear_color(glm::vec4(0.95, 0.48, 0.14, 1));

	wrench::Camera camera(renderer);

	camera.set_position({0, 0, 4});
	camera.set_rotation({0, 0, 0});
	camera.generate_perspective(glm::radians(90.f), 0.01f, 1000.f);
	//alternative : camera.generate_ortho(-2.f, 2.f, -2.f,2.f,0.01f, 1000.f);

	wrench::Transform transform;

	wrench::RenderStates states;

	states.shader = &shader;
	states.camera = &camera;
	states.transform = &transform;

	while (window.is_open())
	{
		//Update events and stuff
		if (window.update())
		{
			//Clear the screen
			renderer->clear();

			transform.rotation.y += glm::radians(window.get_delta_time().as_milliseconds() / 15.f);
			transform.rotation.x += glm::radians(window.get_delta_time().as_milliseconds() / 50.f);

			//Bind the shader
			shader.bind();

			//Draw the VAO
			renderer->draw_object(VAO, states);

			//Swap the buffers
			window.display();
		}
	}

	//Quit the engine
	wrench::quit();
	return 0;
}
