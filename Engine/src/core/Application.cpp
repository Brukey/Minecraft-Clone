#include "Application.h"
#include "Window.h"
#include <GL/glew.h>
#include <chrono>

namespace Engine {
	void Application::Start() {
		Window::CreateWindow(1020, 720, "Window");

		OnStart();
	}

	void Application::Run() {
		m_running = true;
		m_updateThread = std::thread(&Application::UpdateThread, this);

		while (m_running = !Window::ShouldClose()) {
			// Render as fast as possible
			Render();
			Window::SwapBuffers();
			Window::Update();
		}

		m_updateThread.join();
	}

	void Application::Render() {

	}


	void Application::UpdateThread() {
		auto previous = std::chrono::steady_clock::now();
		while (m_running) {
			auto now = std::chrono::steady_clock::now();
			uint32_t timeDifferenceMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(now - previous).count();
			previous = now;

			float dt = (float)timeDifferenceMicroseconds / 1000000.0f;
			OnUpdate(dt);
		}
	}

	void Application::OnClose() {
		Window::Close();
	}


}