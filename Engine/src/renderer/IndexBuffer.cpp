#include "IndexBuffer.h"
#include <GL/glew.h>
#include "core/Logger.h"

namespace Engine {
	static uint32_t s_boundIndexBuffer = 0;

	std::shared_ptr<IndexBuffer> IndexBuffer::Create() {
		std::shared_ptr<IndexBuffer> ibo = std::make_shared<IndexBuffer>();

		glGenBuffers(1, &ibo->m_rendererId);

		return ibo;
	}

	IndexBuffer::~IndexBuffer() {
		if (s_boundIndexBuffer == m_rendererId)
			Unbind();
		glDeleteBuffers(1, &m_rendererId);
		
	}
	
	void IndexBuffer::Bind() const {
		s_boundIndexBuffer = m_rendererId;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
	}

	void IndexBuffer::Unbind() const {
		ASSERT(s_boundIndexBuffer == m_rendererId);

		s_boundIndexBuffer = 0;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);

	}
	
	void IndexBuffer::SetBufferData(const uint32_t* indices, uint32_t numIndices) {
		ASSERT(s_boundIndexBuffer == m_rendererId);
		m_numIndices = numIndices;
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * numIndices, indices, GL_STATIC_DRAW);
	}
}