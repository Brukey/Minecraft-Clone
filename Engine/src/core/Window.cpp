#include "Window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>

namespace Engine {

	static GLFWwindow* s_window = NULL;

	void Window::CreateWindow(int width, int height, const char* title) {
		if (!glfwInit()) {
			fprintf(stderr, "Could not create a Window!\n");
		}

		s_window = glfwCreateWindow(width, height, title, NULL, NULL);
		glfwMakeContextCurrent(s_window);

		// glewInit
		if (glewInit() != GLEW_OK) {
			fprintf(stderr, "Failed to load opengl functions!\n");
		}


	}

	void Window::Close() {
		glfwDestroyWindow(s_window);
		glfwTerminate();
	}

	void Window::Update() {
		glfwSwapBuffers(s_window);
		glfwPollEvents();
	}

	bool Window::ShouldClose() {
		return glfwWindowShouldClose(s_window);
	}
}