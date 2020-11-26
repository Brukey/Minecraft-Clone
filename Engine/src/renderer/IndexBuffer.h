#pragma once

#include <memory>
#include <stdint.h>
#include <vector>

namespace Engine {


	class IndexBuffer {
	public:
		static std::shared_ptr<IndexBuffer> Create();
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		void SetBufferData(const uint32_t* indices, uint32_t numIndices);

		inline uint32_t GetIndexCount() const { return m_numIndices; }
	private:
		uint32_t m_rendererId;
		uint32_t m_numIndices;
	};
}