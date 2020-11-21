#include <iostream>
#include "core/Entrypoint.h"
#include "core/Window.h"
#include "core/Application.h"
#include "core/EventManager.h"

void keypressed(const Engine::KeyPressedEvent& e) {
	printf("%d\n", e.keycode);
}


void OnClose(const Engine::WindowCloseEvent& e) {
	printf("WindowClose\n");
}

void resized(const Engine::WindowResizeEvent& e) {
	printf("Window resized: %d, %d\n", e.width, e.height);
}

class App : public Engine::Application {
	void OnStart() override {
		Engine::Window::SetTitle("Minecraft-clone");
		Engine::EventManager::Subscribe<Engine::WindowCloseEvent>(::OnClose);
		Engine::EventManager::Subscribe<Engine::KeyPressedEvent>(keypressed);
		Engine::EventManager::Subscribe<Engine::WindowResizeEvent>(resized);
	}

	void OnUpdate(float timestep) override {

	}
};

Engine::Application* CreateApplication() {
	return (Engine::Application*) new App;
}
