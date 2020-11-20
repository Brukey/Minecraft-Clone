#include "Shader.h"
#include <GL/glew.h>
#include "core/Logger.h"
#include <fstream>
#include <string>


namespace Engine {

	static uint32_t s_usedProgram = 0;

	static uint32_t CompileShader(const char* content, uint32_t size, uint32_t shaderType) {
		uint32_t shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &content, (int32_t*) &size);
		glCompileShader(shader);
		int32_t status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE) {
			// log error
			char error[1024];
			int len;
			glGetShaderInfoLog(shader, sizeof(error), &len, error);
			error[len] = 0;
			const char* shaderTypeString;
			switch (shaderType) {
			case GL_VERTEX_SHADER:
				shaderTypeString = "VertexShader";
				break;
			case GL_FRAGMENT_SHADER:
				shaderTypeString = "FragmentShader";
				break;
			}
			LOG("[ERROR] in %s: %s\n", shaderTypeString, error);
		}
		return shader;
	}

	std::shared_ptr<Shader> Shader::CreateFromFile(const char* filepath) {
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();


		// read source
		std::ifstream file(filepath);
		ASSERT(file.is_open());

		std::string vertexSource;
		std::string fragmentSource;
		std::string* currentSource = NULL;
		std::string line;
		while (std::getline(file, line)) {
			if (line.find("#vertex") != std::string::npos)
				currentSource = &vertexSource;
			else if (line.find("#fragment") != std::string::npos)
				currentSource = &fragmentSource;
			else if (currentSource) {
				currentSource->append(line);
				currentSource->append("\n");
			}
				
		}

		file.close();

		shader->m_rendererId = glCreateProgram();
		// compile shader source
		uint32_t vertexShader = CompileShader(vertexSource.c_str(), (uint32_t) vertexSource.size(), GL_VERTEX_SHADER);
		uint32_t fragmentShader = CompileShader(fragmentSource.c_str(), (uint32_t) fragmentSource.size(), GL_FRAGMENT_SHADER);

		// link vertex and fragment shader

		glAttachShader(shader->m_rendererId, vertexShader);
		glAttachShader(shader->m_rendererId, fragmentShader);
		glLinkProgram(shader->m_rendererId);
		glValidateProgram(shader->m_rendererId);

		int32_t linkStatus;
		glGetProgramiv(shader->m_rendererId, GL_LINK_STATUS, &linkStatus);
		if (linkStatus == GL_FALSE) {
			char error[1024];
			int len;
			glGetProgramInfoLog(shader->m_rendererId, sizeof(error), &len, error);
			error[len] = 0;
			LOG("Failed to link shader: %s\n", error);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return shader;
	}

	Shader::~Shader() {
		if (s_usedProgram == m_rendererId)
			Unbind();
		glDeleteProgram(m_rendererId);
	}

	void Shader::Bind() const {
		s_usedProgram = m_rendererId;
		glUseProgram(s_usedProgram);
	}

	void Shader::Unbind() const {
		ASSERT(s_usedProgram == m_rendererId);
		s_usedProgram = 0;
		glUseProgram(0);
	}
}