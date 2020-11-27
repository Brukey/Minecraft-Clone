#pragma once

#include <unordered_map>
#include <stdint.h>
#include <memory>
#include <glm/glm.hpp>

namespace Engine {

	class Shader {
	public:
		static std::shared_ptr<Shader> CreateFromFile(const char* filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetMat4(const char* name, const glm::mat4& mat) const;
		void SetFloat(const char* name, float val) const;
		void SetFloat3(const char* name, const glm::vec3& v) const { SetFloat3(name, v.x, v.y, v.z); }
		void SetFloat3(const char* name, float x, float y, float z) const;
		void SetFloat4(const char* name, const glm::vec4& v) const { SetFloat4(name, v.x, v.y, v.z, v.w); }
		void SetFloat4(const char* name, float x, float y, float z, float w) const;
		void SetFloat2(const char* name, const glm::vec2& v) const { SetFloat2(name, v.x, v.y); }
		void SetFloat2(const char* name, float x, float y) const;
		void SetFloatArray(const char* name, const float* values, uint32_t numValues) const;

		void SetInt(const char* name, int32_t value) const;
		void SetInt2(const char* name, int32_t x, int32_t y) const;
		void SetInt3(const char* name, int32_t x, int32_t y, int32_t z) const;
		void SetInt4(const char* name, int32_t x, int32_t y, int32_t z, int32_t w) const;
		void SetIntArray(const char* name, int32_t* values, uint32_t numValues) const;

	private:

		int32_t GetUniformLocation(const char* name) const;

		mutable std::unordered_map<std::string, int32_t> m_uniformLocations;

		uint32_t m_rendererId;
	};
}