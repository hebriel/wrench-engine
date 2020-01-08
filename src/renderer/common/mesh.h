//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include <utility>
#include <vector>
#include "vertex_array.h"

namespace wrench {

	class Mesh
	{

	public:
		Mesh();

		std::vector<float> vertices;
		std::vector<unsigned> indices;

		template <class VAOImpl, class VBOImpl, class IBOImpl>
		void setup_mesh(const Layout& layout)
		{
			m_layout = layout;
			setup_mesh<VAOImpl, VBOImpl, IBOImpl>();
		}

		template <class VAOImpl, class VBOImpl, class IBOImpl>
		void setup_mesh()
		{
			static_assert(std::is_base_of_v<VertexArray, VAOImpl>, "Template type parameter should inherit wrench::VertexArray");
			static_assert(std::is_base_of_v<VertexBuffer, VBOImpl>, "Template type parameter should inherit wrench::VertexBuffer");
			static_assert(std::is_base_of_v<IndexBuffer, IBOImpl>, "Template type parameter should inherit wrench::IndexBuffer");

			m_vbo = wrench::VertexBuffer::create<VBOImpl>(vertices.data(), vertices.size() * sizeof(float));
			m_vbo->bind();
			m_vbo->setLayout(m_layout);

			//Create our Index Buffer
			m_ibo = wrench::IndexBuffer::create<IBOImpl>(indices.data(), indices.size() * sizeof(unsigned int));
			m_ibo->bind();

			//Create our Vertex Array and attach the Vertex Buffer Object and the Index Buffer
			m_vao = wrench::VertexArray::create<VAOImpl>();
			m_vao->add_vertex_buffer(m_vbo);
			m_vao->set_index_buffer(m_ibo);
		}

		[[nodiscard]] const std::shared_ptr<VertexArray>& get_vertex_array() const {return m_vao;}

	private:
		std::shared_ptr<VertexArray> m_vao {nullptr};
		std::shared_ptr<VertexBuffer> m_vbo {nullptr};
		std::shared_ptr<IndexBuffer> m_ibo {nullptr};
		Layout m_layout {};
	};
}
