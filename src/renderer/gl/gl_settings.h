//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

namespace wrench::gl {

	/**
 	* @brief Structure used to configure an OpenGL context
 	*/
	struct GLSettings
	{
		/**
		* @brief The OpenGL major version (the 3 in 'OpenGL 3.2')
		*/
		int			majorVersion		{3};

		/**
		* @brief The OpenGL minor version (the 2 in 'OpenGL 3.2')
		*/
		int			minorVersion		{2};

		/**
		* @brief Tell whether or not OpenGL should use the Core profile
		*/
		bool		useCore				{true};

		/**
		* @brief Tell whether or not OpenGL should enable Double Buffering
		*/
		bool 		useDoubleBuffering	{true};
	};
}
