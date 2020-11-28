#include "Input.h"
#include "Window.h"
#include <GLFW/glfw3.h>

namespace Engine {

	static uint32_t mousePrevX = 0xFFFFFFFF;
	static uint32_t mousePrevY = 0xFFFFFFFF;

	bool Input::IsKeyDown(Key keycode) {
		GLFWwindow* window = (GLFWwindow*) Window::GetNativeWindow();
		int state = glfwGetKey(window, keycode);
		
		return state == GLFW_PRESS;
	}

	void Input::SetMousePosition(uint32_t x, uint32_t y, int32_t* deltaX, int32_t* deltaY) {
		if (deltaX && deltaY) {
			// calculate delta position
			if (mousePrevX == 0xFFFFFFFF) {
				*deltaX = 0;
				*deltaY = 0;
			}else {
				*deltaX = (int32_t)x - mousePrevX;
				*deltaY = (int32_t)y - mousePrevY;
			}
		}
		mousePrevX = x;
		mousePrevY = y;
	}
}