#include "Application.h"
#include "Window.h"
#include <GL/glew.h>

namespace Engine {
	void Application::Start() {
		Engine::Window::CreateWindow(1020, 720, "Window");

		OnStart();
	}

	void Application::Run() {
		
		while (!Engine::Window::ShouldClose()) {
			Engine::Window::Update();
			OnUpdate(1.0f / 60.0f); // asume 60 frames per second
		}
		
	}

	void Application::OnClose() {
		Engine::Window::Close();
	}
}