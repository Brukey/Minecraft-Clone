#include "VertexBuffer.h"
#include <GL/glew.h>
#include "core/Logger.h"

namespace Engine {

	static uint32_t s_boundVertexBuffer = 0;
	
	std::shared_ptr<VertexBuffer> VertexBuffer::Create() {
		std::shared_ptr<VertexBuffer> vbo = std::make_shared<VertexBuffer>();

		glGenBuffers(1, &vbo->m_rendererId);

		return vbo;
	}

	void VertexBuffer::Bind() const {
		if (s_boundVertexBuffer != m_rendererId) {
			glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
			s_boundVertexBuffer = m_rendererId;
		}
	}

	void VertexBuffer::Unbind() const {
		if (s_boundVertexBuffer == m_rendererId) {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			s_boundVertexBuffer = 0;
		}
	}

	void VertexBuffer::SetBufferData(const void* data, uint32_t size) {
		ASSERT(m_rendererId == s_boundVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void VertexBuffer::SetLayout(const VertexBufferLayout& layout) {
		ASSERT(m_rendererId == s_boundVertexBuffer);
		uint64_t offset = 0;
		for (const VertexBufferLayout::BufferElement& element : layout.elements) {
			glEnableVertexAttribArray(element.location);

			glVertexAttribPointer(element.location, element.numDimensions, GL_FLOAT, GL_FALSE, layout.stride, (const void*) offset);
			offset += sizeof(float) * element.numDimensions;
		}
	}
}