//
// @authors {underdisk}
// License : LGPLv3
//

#include "window/window.h"
#include "renderer/gl/gl_context.h"

int main()
{
	wrench::init();

	wrench::GLSettings settings;
	settings.useDoubleBuffering = true;
	settings.useCore = true;
	settings.minorVersion = 4;
	settings.minorVersion = 1;

	wrench::Window window({800, 600}, "Default Window");
	window.initContext<wrench::GLContext>(settings);

	glClearColor(1, 1, 1, 1);

	while (window.isOpen())
	{
		window.update();
		glClear(GL_COLOR_BUFFER_BIT);
		window.display();
	}

	wrench::quit();
	return 0;
}
