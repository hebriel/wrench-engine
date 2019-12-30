//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

namespace wrench {

	/**
 	* @brief Structure used to configure OpenGL
 	*/
	struct GLSettings
	{
		int			majorVersion		{3};
		int			minorVersion		{2};
		bool		useCore				{true};
		bool 		useDoubleBuffering	{true};
	};
}
