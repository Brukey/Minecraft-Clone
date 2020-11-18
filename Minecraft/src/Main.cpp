#include <iostream>
#include "core/Entrypoint.h"
#include "core/Window.h"
#include "core/Application.h"
#include "core/EventManager.h"

void handler(const Engine::KeyPressedEvent& e) {
	printf("%d\n", e.keycode);
}


void OnClose(const Engine::WindowCloseEvent& e) {
	printf("WindowClose\n");
}

class App : public Engine::Application {
	void OnStart() override {

		Engine::KeyPressedEvent e;
		e.keycode = 5;
		Engine::EventManager::Subscribe<Engine::KeyPressedEvent>(handler);
		Engine::EventManager::Publish(e);

		Engine::EventManager::Subscribe<Engine::WindowCloseEvent>(::OnClose);
		Engine::WindowCloseEvent e2;
		Engine::EventManager::Publish(e2);

	}

	void OnUpdate(float timestep) override {

	}
};

Engine::Application* CreateApplication() {
	return (Engine::Application*) new App;
}
