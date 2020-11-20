#pragma once

#include <stdint.h>

namespace Engine {

	class RenderCommand {
	public:
		static void InitContext();
		static void DrawIndexed(uint32_t numIndices);
		static void ClearColorBuffer();
	};
}