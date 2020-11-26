#pragma once

#include <memory>
#include <stdint.h>

namespace Engine {

	class VertexArray {
	public:
		static std::shared_ptr<VertexArray> Create();
		~VertexArray();

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t m_rendererId;
	};

}