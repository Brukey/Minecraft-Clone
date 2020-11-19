#include "Application.h"
#include "Window.h"
#include <GL/glew.h>

namespace Engine {
	void Application::Start() {
		Window::CreateWindow(1020, 720, "Window");

		OnStart();
	}

	void Application::Run() {
		
		while (!Window::ShouldClose()) {
			Window::Update();
			OnUpdate(1.0f / 60.0f); // asume 60 frames per second
		}
		
	}

	void Application::OnClose() {
		Window::Close();
	}
}