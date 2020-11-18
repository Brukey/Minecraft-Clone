#include <iostream>
#include "core/Entrypoint.h"
#include "core/Window.h"
#include "core/Application.h"


class App : public Engine::Application {
	void OnStart() override {

	}

	void OnUpdate(float timestep) override {

	}
};

Engine::Application* CreateApplication() {
	return (Engine::Application*) new App;
}
