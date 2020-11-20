#pragma once

#include <stdint.h>
#include <stdint.h>

namespace Engine {

	class RenderCommand {
	public:
		static void InitContext();
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		static void DrawIndexed(uint32_t numIndices);
		static void ClearColorBuffer();
	};
}