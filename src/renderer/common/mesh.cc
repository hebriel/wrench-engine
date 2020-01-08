//
// @authors {underdisk}
// License : LGPLv3
//

#include "mesh.h"

namespace wrench {

	Mesh::Mesh()
	{
		m_layout = {
				{wrench::DataType::Vec3, "a_Position"},
				{wrench::DataType::Vec3, "a_Normal"},
				{wrench::DataType::Vec2, "a_TexCoord"},
		};
	}
}
