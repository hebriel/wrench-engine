//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#if __cplusplus < 201703L
	#ifndef WRENCH_IGNORE_STDCPP17
		#error Your compiler either do not support C++17 or you did not enable it
	#endif
#endif

#define WRENCH_VERSION_MAJOR	0
#define WRENCH_VERSION_MINOR	1
#define WRENCH_VERSION_PATCH	1

namespace wrench {

	/**
	* @brief Inits the engine and its dependencies
	*/
	void init();

	/**
	* @brief Quit the engine and its dependencies
	*/
	void quit();
}
