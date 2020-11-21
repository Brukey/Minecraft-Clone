#pragma once

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
	};

}

