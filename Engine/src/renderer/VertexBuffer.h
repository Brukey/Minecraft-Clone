#pragma once

#include <memory>
#include <stdint.h>
#include <vector>

namespace Engine {

	struct VertexBufferLayout {
		struct BufferElement {
			uint32_t location;
			uint32_t numDimensions;
		};

		std::vector<BufferElement> elements;
		uint32_t stride;

		void PushFloat(uint32_t location, uint32_t dimensions) {
			stride += sizeof(float) * dimensions;
			elements.emplace_back(location, dimensions);
		}
	};

	class VertexBuffer {
	public:
		static std::shared_ptr<VertexBuffer> Create();

		void Bind() const;
		void Unbind() const;

		void SetBufferData(const void* data, uint32_t size);
		void SetLayout(const VertexBufferLayout& layout);

	private:
		uint32_t m_rendererId;
	};
}