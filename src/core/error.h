//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include <iostream>
#include <string>

namespace wrench {

	struct Error
	{
		bool err		{false};
		std::string msg	{"No Error"};
	};

	void crash_on_fail(const Error& err)
	{
		if (err.err)
			throw std::runtime_error("ERROR:" + err.msg);
	}

	void inform_on_fail(const Error& err, std::ostream& outputStream = std::cerr)
	{
		if (err.err)
			outputStream << "ERROR: " << err.msg << std::endl;
	}
}
