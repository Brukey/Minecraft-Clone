#include "VertexArray.h"
#include <GL/glew.h>
#include "core/Logger.h"

namespace Engine {

	static uint32_t s_boundVao = 0;

	std::shared_ptr<VertexArray> VertexArray::Create() {
		std::shared_ptr<VertexArray> vao = std::make_shared<VertexArray>();
		
		glGenVertexArrays(1, &vao->m_rendererId);

		return vao;
	}

	VertexArray::~VertexArray() {
		if (s_boundVao == m_rendererId)
			Unbind();
		glDeleteVertexArrays(1, &m_rendererId);
	}

	void VertexArray::Bind() const {
		s_boundVao = m_rendererId;
		glBindVertexArray(m_rendererId);
	}

	void VertexArray::Unbind() const {
		ASSERT(s_boundVao == m_rendererId);
		s_boundVao = 0;
		glBindVertexArray(0);
	}
}