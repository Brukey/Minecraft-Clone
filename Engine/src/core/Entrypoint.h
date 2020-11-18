#pragma once

#include "Application.h"

extern Engine::Application* CreateApplication();

int main(const int argc, const char** argv) {
	Engine::Application* app = CreateApplication();

	app->Start();
	app->Run();
	app->OnClose();

	delete app;
	return 0;
}