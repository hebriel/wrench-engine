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
#include <renderer/common/mesh.h>
#include <renderer/common/resource_loader.h>
#include <renderer/common/object.h>

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

	wrench::ResourceLoader<wrench::gl::GLVertexArray, wrench::gl::GLVertexBuffer, wrench::gl::GLIndexBuffer> loader;

	loader.load_mesh("main_mesh", "resources/teapot.obj");

	window.set_framerate_limit(10000);

	auto renderer = wrench::Renderer::create<wrench::gl::GLRenderer>(window);

	//Create a shader
	wrench::gl::GLShader shader;

	//Search the shader files, compiling them, and linking them
	shader
		.add_vertex_shader_by_file("resources/flat_color.mat/shader.vert")
		.add_fragment_shader_by_file("resources/flat_color.mat/shader.frag")
		.link();

	std::vector<wrench::Mesh>& mesh = loader.get_mesh("main_mesh");

	renderer->change_clear_color(glm::vec4(0.95, 0.48, 0.14, 1));

	wrench::Camera camera(renderer);

	camera.set_position({0, 0, 6.5f});
	camera.set_rotation({0, 0, 0});
	camera.generate_perspective(glm::radians(90.f), 0.01f, 1000.f);
	//alternative : camera.generate_ortho(-2.f, 2.f, -2.f,2.f,0.01f, 1000.f);

	wrench::Object obj(mesh);
	obj.states.camera = &camera;
	obj.states.shader = &shader;

	float totalTime;

	while (window.is_open())
	{
		//Update events and stuff
		if (window.update())
		{
			totalTime += window.get_delta_time().as_seconds();
			//Clear the screen
			renderer->clear();

			obj.transform.rotation.y = glm::radians(std::sin(totalTime * 0.9f)) * 98.f;
			obj.transform.rotation.x = glm::radians(std::sin(totalTime * 1.8f)) * 20.f;

			//Bind the shader
			shader.bind();

			//Draw the VAO
			renderer->draw_object(obj);

			//Swap the buffers
			window.display();
		}
	}

	//Quit the engine
	wrench::quit();
	return 0;
}
