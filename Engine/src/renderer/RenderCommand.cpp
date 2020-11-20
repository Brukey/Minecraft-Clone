#include "RenderCommand.h"
#include <GL/glew.h>
#include "core/Logger.h"

namespace Engine {

	void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
		if(severity > GL_DEBUG_SEVERITY_MEDIUM)
			LOG("Opengl error: %s\n", message);
	}

	void RenderCommand::InitContext() {
		glCullFace(GL_BACK);
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, NULL);
	}

	void RenderCommand::DrawIndexed(uint32_t numIndices) {
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, NULL);
	}

	void RenderCommand::ClearColorBuffer() {
		glClear(GL_COLOR_BUFFER_BIT);
	}
}