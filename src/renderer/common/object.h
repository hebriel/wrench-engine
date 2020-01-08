//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include "render_states.h"
#include "mesh.h"

namespace wrench {

	class Object
	{
	public:

		explicit Object(const std::vector<Mesh>& meshes = {{}})
			: m_meshes(meshes)
		{
			states.transform = &transform;
		}

		RenderStates states;
		const std::vector<Mesh>& m_meshes;
		Transform transform {{0, 0, 0}, {0, 0, 0}, {1, 1, 1}};
	};
}
