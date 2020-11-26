#include <iostream>
#include "core/Entrypoint.h"
#include "core/Window.h"
#include "core/Application.h"
#include "core/EventManager.h"

#include "renderer/Shader.h"
#include "renderer/VertexArray.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexBuffer.h"
#include "renderer/RenderCommand.h"

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


		// setup render data

		shader = Engine::Shader::CreateFromFile("res/shaders/Shader.glsl");

		float vertices[] = {
			-0.5f, -0.5f, 
			0.5f, -0.5f, 
			0.0f, 0.5f
		};


		uint32_t indices[3] = { 0, 1, 2 };

		vao = Engine::VertexArray::Create();
		vao->Bind();

		Engine::VertexBufferLayout layout;
		layout.PushFloat(0, 2);

		vbo = Engine::VertexBuffer::Create();
		vbo->Bind();
		vbo->SetBufferData(vertices, sizeof(vertices));
		vbo->SetLayout(layout);

		ibo = Engine::IndexBuffer::Create();
		ibo->Bind();
		ibo->SetBufferData(indices, 3);
	}

	void OnRender() const override {
		Engine::RenderCommand::ClearColorBuffer();
		shader->Bind();
		vao->Bind();
		Engine::RenderCommand::DrawIndexed(ibo->GetIndexCount());
	}

	void OnUpdate(float timestep) override {

	}

	std::shared_ptr<Engine::Shader> shader;
	std::shared_ptr<Engine::VertexArray> vao;
	std::shared_ptr<Engine::VertexBuffer> vbo;
	std::shared_ptr<Engine::IndexBuffer> ibo;
};

Engine::Application* CreateApplication() {
	return (Engine::Application*) new App;
}
