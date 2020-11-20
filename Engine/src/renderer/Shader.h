#pragma once

#include <unordered_map>
#include <stdint.h>
#include <memory>

namespace Engine {

	class Shader {
	public:
		static std::shared_ptr<Shader> CreateFromFile(const char* filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;



	private:
		uint32_t m_rendererId;
	};
}