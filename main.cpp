//
// @authors {underdisk}
// License : LGPLv3
//

#include <iostream>
#include "window/window.h"

int main()
{
	wrench::init();
	wrench::Window window({800, 600}, "Default Window");

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
