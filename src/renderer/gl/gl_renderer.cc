//
// @authors {underdisk}
// License : LGPLv3
//

#include "gl_renderer.h"
#include "../common/render_states.h"
#include "../common/object.h"
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/transform.hpp>

namespace wrench::gl {

	void GLRenderer::draw_object(const std::weak_ptr<VertexArray>& vertexArray) const
	{
		if (auto spt = vertexArray.lock())
		{
			spt->bind();
			glDrawElements(GL_TRIANGLES, spt->get_index_buffer()->get_count(), GL_UNSIGNED_INT, nullptr);
		}
	}

	void GLRenderer::change_clear_color(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void GLRenderer::change_clear_color(const glm::ivec4& color)
	{
		glClearColor(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
	}

	void GLRenderer::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GLRenderer::draw_object(const std::weak_ptr<VertexArray> &vertexArray, const RenderStates& states) const
	{
		if(states.shader == nullptr || states.camera == nullptr || states.transform == nullptr)
			return;

		if (auto spt = vertexArray.lock())
		{
			states.shader->bind();
			glm::mat4 model(1.0f);

			model = glm::translate(model, states.transform->position);

			model = glm::rotate(model, states.transform->rotation.x, {1, 0, 0});
			model = glm::rotate(model, states.transform->rotation.y, {0, 1, 0});
			model = glm::rotate(model, states.transform->rotation.z, {0, 0, 1});

			model = glm::scale(model, states.transform->scale);

			states.shader->set_uniform("w_mvp", states.camera->get_view_projection_matrix() * model);
			spt->bind();
			glDrawElements(GL_TRIANGLES, spt->get_index_buffer()->get_count(), GL_UNSIGNED_INT, nullptr);
			states.shader->unbind();
		}
	}

	void GLRenderer::draw_object(const Object& object) const
	{
		if(object.states.shader == nullptr || object.states.camera == nullptr || object.states.transform == nullptr)
			return;

		for (const auto& mesh : object.m_meshes)
		{
			object.states.shader->bind();
			glm::mat4 model(1.0f);

			model = glm::translate(model, object.states.transform->position);

			model = glm::rotate(model, object.states.transform->rotation.x, {1, 0, 0});
			model = glm::rotate(model, object.states.transform->rotation.y, {0, 1, 0});
			model = glm::rotate(model, object.states.transform->rotation.z, {0, 0, 1});

			model = glm::scale(model, object.states.transform->scale);

			object.states.shader->set_uniform("w_mvp", object.states.camera->get_view_projection_matrix() * model);
			mesh.get_vertex_array()->bind();
			glDrawElements(GL_TRIANGLES, mesh.get_vertex_array()->get_index_buffer()->get_count(), GL_UNSIGNED_INT, nullptr);
			object.states.shader->unbind();
		}
	}
}