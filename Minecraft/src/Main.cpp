#include <Engine.h>
#include <core/Entrypoint.h>

#include "types/Block.h"
#include "types/Chunk.h"
#include "meshgenerator/MeshBuilder.h"
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Minecraft {

	class App : public Engine::Application {
		void OnStart() override {
			Engine::Window::SetTitle("Minecraft-clone");
			Engine::EventManager::Subscribe<Engine::WindowResizeEvent>(std::bind(&App::OnResize, this, std::placeholders::_1));
			BlockRegistry::Initialize();


			// setup render data
			for (int32_t x = 0; x < 3; x++) {
				for (int32_t z = 0; z < 3; z++) {
					Chunk chunk{Vec3i(x, 0, -z)};

					for (uint32_t i = 0; i < CHUNK_SIZE; i++) {
						for (uint32_t j = 0; j < CHUNK_SIZE; j++) {
							for (uint32_t k = 0; k < CHUNK_SIZE / 2; k++) {
								chunk.Set(Block::Dirt, i, k, j);
							}
						}
					}
					loadedChunks.push_back(chunk);
				}
			}

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



			tex = Engine::Texture::CreateFromFile("res/textures/grass.png");
			float aspectRatio = (float) Engine::Window::GetWidth() / Engine::Window::GetHeight();
			cameramatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 2.0f, 5.0f));
			projectionmatrix = glm::perspective(3.1415f * 0.5f, aspectRatio, 0.1f, 100.0f);

		}




		void OnRender() const override {
			Engine::RenderCommand::ClearColorBuffer();
			tex->Bind();
			shader->Bind();
			shader->SetMat4("projectionmatrix", projectionmatrix * glm::inverse(cameramatrix));
			vao->Bind();

			for (Chunk& chunk : loadedChunks) {
				if (chunk.IsDirty()) {
					// regenerate mesh
					MeshBuilder::Generate(chunk);
				}
				chunk.GetVertexArray()->Bind();
				uint32_t numIndices = chunk.GetNumMeshIndices();
				Engine::RenderCommand::DrawIndexed(numIndices);
			}
		}

		void OnUpdate(float timestep) override {

		}

		void OnResize(const Engine::WindowResizeEvent& e) {
			Engine::RenderCommand::SetViewport(0, 0, e.width, e.height);
			float aspectRatio = (float)e.width / e.height;
			projectionmatrix = glm::perspective(3.1415f * 0.5f, aspectRatio, 0.1f, 100.0f) *
				glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
		}

		mutable std::vector<Chunk> loadedChunks;
		glm::mat4 projectionmatrix;
		glm::mat4 cameramatrix;
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
