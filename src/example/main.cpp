//
// @authors {underdisk}
// License : LGPLv3
//

#include "../window/window.h"
#include "../renderer/gl/gl_context.h"
#include "../renderer/gl/gl_shader.h"

int main()
{
	wrench::init();

	//OpenGL 4.1
	wrench::GLSettings settings;
	settings.useDoubleBuffering = true;
	settings.useCore = true;
	settings.majorVersion = 4;
	settings.minorVersion = 1;

	wrench::Window window({800, 600}, "Wrench : Example");
	window.initContext<wrench::GLContext>(settings);

	glClearColor(0.95, 0.48, 0.14, 1);

	wrench::GLShader shader;

	shader
		.add_vertex_shader_by_file("resources/shader.vert")
		.add_fragment_shader_by_file("resources/shader.frag")
		.link();

	unsigned VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	unsigned indices[3] = {
		0, 1, 2,
	};

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	while (window.isOpen())
	{
		window.update();
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(VAO);
		shader.bind();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
		window.display();
	}

	wrench::quit();
	return 0;
}
