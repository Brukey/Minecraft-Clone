#include "RenderCommand.h"
#include <GL/glew.h>
#include "core/Logger.h"

namespace Engine {

	void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
		const char* messageType;
		switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:
			messageType = "ERROR";
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			messageType = "WARNING";
			break;
		case GL_DEBUG_SEVERITY_LOW:
			messageType = "PERFORMANCE INFO";
			break;
		default:
			messageType = "INFO";
			return;
		}

		LOG("[Opengl %s]: %s\n", messageType, message);
	}

	void RenderCommand::InitContext() {
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glClearColor(0.2f, 0.2f, 0.2, 1.0f);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
#ifdef DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, NULL);
#endif //DEBUG
	}

	void RenderCommand::DrawIndexed(uint32_t numIndices) {
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, NULL);
	}

	void RenderCommand::ClearColorBuffer() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
		glViewport(x, y, width, height);
	}
}