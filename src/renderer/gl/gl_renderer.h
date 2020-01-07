//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include "../common/renderer.h"
#include "../common/camera.h"

namespace wrench::gl {

	/**
	* @brief OpenGL implementation of a Renderer
	*/
	class GLRenderer final : public Renderer
	{
	public:
		using Renderer::Renderer;

		void draw_object(const std::weak_ptr<VertexArray> &vertexArray) const override;

		void draw_object(const std::weak_ptr<VertexArray> &vertexArray, const RenderStates& states) const override;

		void change_clear_color(const glm::vec4 &color) override;

		void change_clear_color(const glm::ivec4& color) override;

		void clear() override;
	};
}
