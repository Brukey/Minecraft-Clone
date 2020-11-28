#pragma once

#include <stdint.h>

namespace Engine {

	class Window
	{
	public:
		static void CreateWindow(int width, int height,const char* title);
		static void Update();
		static void SwapBuffers();
		static bool ShouldClose();
		static void Close();
		static void SetTitle(const char* title);

		static uint32_t GetWidth();
		static uint32_t GetHeight();
		static void* GetNativeWindow();

	};

}

