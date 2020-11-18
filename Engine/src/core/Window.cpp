#include "Window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Engine {

	static GLFWwindow* s_window = NULL;

	void Window::CreateWindow(int width, int height, const char* title) {
		if (!glfwInit()) {
			std::cerr << "Could not create a Window!" << std::endl;
		}

		s_window = glfwCreateWindow(width, height, title, NULL, NULL);

	}

	void Window::Close() {
	}

}