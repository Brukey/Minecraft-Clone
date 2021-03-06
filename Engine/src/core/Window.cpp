#include "Window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "EventManager.h"
#include "Input.h"

namespace Engine {

	static GLFWwindow* s_window = NULL;
	static bool s_cursorEnabled = false;

	void Window::CreateWindow(int width, int height, const char* title) {
		if (!glfwInit()) {
			fprintf(stderr, "Could not create a Window!\n");
		}
		
		s_window = glfwCreateWindow(width, height, title, NULL, NULL);
		glfwMakeContextCurrent(s_window);
		SetCursor(false);

		// glewInit
		if (glewInit() != GLEW_OK) {
			fprintf(stderr, "Failed to load opengl functions!\n");
		}

		glfwSetKeyCallback(s_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			if (action == GLFW_PRESS) {
				KeyPressedEvent e;
				e.keycode = (uint32_t) key;
				EventManager::Publish(e);
			}else {
				KeyReleasedEvent e;
				e.keycode = (uint32_t) key;
				EventManager::Publish(e);
			}
		});

		glfwSetCursorPosCallback(s_window, [](GLFWwindow* window, double xpos, double ypos) {
			MouseMoveEvent e{ (uint32_t)xpos, (uint32_t)ypos };
			EventManager::Publish(e);
		});

		glfwSetMouseButtonCallback(s_window, [](GLFWwindow* window, int button, int action, int mods) {
			// if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
			if (action == GLFW_PRESS) {
				MousePressedEvent e;
				e.button = (uint32_t) button;
				EventManager::Publish(e);
			}else {
				MouseReleasedEvent e;
				e.button = (uint32_t) button;
				EventManager::Publish(e);
			}
		});

		glfwSetCursorPosCallback(s_window, [](GLFWwindow* window, double x, double y) {
			MouseMovedEvent e;
			e.x = (uint32_t) x;
			e.y = (uint32_t) y;
			Input::SetMousePosition(e.x, e.y, &e.deltaX, &e.deltaY);
			EventManager::Publish(e);
		});

		glfwSetScrollCallback(s_window, [](GLFWwindow* window, double xoffset, double yoffset) {
			// if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
			MouseScrollEvent e;
			e.x = (int32_t) xoffset;
			e.y = (int32_t) yoffset;
			EventManager::Publish(e);
		});

		glfwSetWindowCloseCallback(s_window, [](GLFWwindow* window) {
			WindowCloseEvent e;
			EventManager::Publish(e);
		});

		glfwSetFramebufferSizeCallback(s_window, [](GLFWwindow* window, int w, int h) {
			WindowResizeEvent e;
			e.width = (uint32_t) w;
			e.height = (uint32_t) h;
			EventManager::Publish(e);
		});
	}

	void Window::SetCursor(bool enabled) {
		
		if(enabled)
			glfwSetInputMode(s_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else
			glfwSetInputMode(s_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		s_cursorEnabled = enabled;
	}

	bool Window::IsCursorEnabled() {
		return s_cursorEnabled;
	}


	void Window::Close() {
		glfwDestroyWindow(s_window);
		glfwTerminate();
	}

	void Window::Update() {
		glfwPollEvents();
	}

	bool Window::ShouldClose() {
		return glfwWindowShouldClose(s_window);
	}

	void Window::SwapBuffers() {
		glfwSwapBuffers(s_window);
	}

	void Window::SetTitle(const char* title) {
		glfwSetWindowTitle(s_window, title);
	}


	uint32_t Window::GetWidth() {
		int32_t x, y;
		glfwGetWindowSize(s_window, &x, &y);
		return x;
	}

	uint32_t Window::GetHeight() {
		int32_t x, y;
		glfwGetWindowSize(s_window, &x, &y);
		return y;
	}

	void* Window::GetNativeWindow() {
		return (void*) s_window;
	}
}