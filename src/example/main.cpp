//
// @authors {underdisk}
// License : LGPLv3
//

#include <window/window.h>
#include <renderer/gl/all.h>

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

	//Create the window
	wrench::Window window({800, 600}, "Wrench : Example");
	//Attach it an OpenGL context
	window.initContext<wrench::gl::GLContext>(settings);

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
		-0.5f, -0.5f, 0.0f, 	1, 0, 0, 1,
		 0.5f, -0.5f, 0.0f, 	0, 1, 0, 1,
		 0.0f,  0.5f, 0.0f, 	0, 0, 1, 1,
	};

	//Here are our indices for our Vertex Buffer Object
	unsigned indices[3] = {
			0, 1, 2,
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
	glClearColor(0.95, 0.48, 0.14, 1);

	while (window.is_open())
	{
		//Updating events and stuff
		window.update();

		//Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		//Bind the Vertex Array
		VAO->bind();

		//Bind the shader
		shader.bind();

		//Draw the bound Vertex Array, with the VBO and the EBO connected to it
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

		//Swap the buffers
		window.display();
	}

	//Quit the engine
	wrench::quit();
	return 0;
}
