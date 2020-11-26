#include <Engine.h>
#include "types/Block.h"
#include "types/Chunk.h"
#include "renderer/Texture.h"


namespace Minecraft {




	class App : public Engine::Application {
		void OnStart() override {
			Engine::Window::SetTitle("Minecraft-clone");
			BlockRegistry::Initialize();

			Chunk chunk;
			LOG("%s\n", chunk.IsDirty() ? "dirty" : "clean");
			chunk.Set(Block::Grass, 0, 0, 0);
			LOG("%s\n", chunk.IsDirty() ? "dirty" : "clean");



			// setup render data

			shader = Engine::Shader::CreateFromFile("res/shaders/Shader.glsl");

			float vertices[] = {
				-0.5f, -0.5f, 0.0f, 0.0f,
				0.5f, -0.5f,  1.0f, 0.0f,
				-0.5f, +0.5f, 0.0f, 1.0f,
				0.5f, +0.5f, 1.0f, 1.0f
			};


			uint32_t indices[6] = { 0, 1, 2 , 1, 3, 2};

			vao = Engine::VertexArray::Create();
			vao->Bind();

			Engine::VertexBufferLayout layout;
			layout.PushFloat(0, 2);
			layout.PushFloat(1, 2);

			vbo = Engine::VertexBuffer::Create();
			vbo->Bind();
			vbo->SetBufferData(vertices, sizeof(vertices));
			vbo->SetLayout(layout);

			ibo = Engine::IndexBuffer::Create();
			ibo->Bind();
			ibo->SetBufferData(indices, 6);


			tex = Engine::Texture::CreateFromFile("res/t1.png");
		}




		void OnRender() const override {
			Engine::RenderCommand::ClearColorBuffer();
			tex->Bind();
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
		std::shared_ptr<Engine::Texture> tex;
	};

}

Engine::Application* CreateApplication() {
	return (Engine::Application*) new Minecraft::App;
}
