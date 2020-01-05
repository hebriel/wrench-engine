//
// @authors {underdisk}
// License : LGPLv3
//

#include "layout.h"

namespace wrench {

	void Layout::calculate()
	{
		char* offset {nullptr};
		for (auto& element : m_elements)
		{
			element.offset = offset;
			offset += element.size;
			m_stride += element.size;
		}
	}
}
