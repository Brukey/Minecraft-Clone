#include <Engine.h>
#include "types/Block.h"
#include "types/Chunk.h"
#include "renderer/Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "renderer/Camera.h"


namespace Minecraft {

	class App : public Engine::Application {
		void OnStart() override {
			Engine::Window::SetTitle("Minecraft-clone");
			Engine::EventManager::Subscribe<Engine::WindowResizeEvent>(std::bind(&App::OnResize, this, std::placeholders::_1));
			Engine::EventManager::Subscribe<Engine::MouseMovedEvent>(std::bind(&App::MouseMoved, this, std::placeholders::_1));
			BlockRegistry::Initialize();


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

			camera = Engine::Camera::Create();

			tex = Engine::Texture::CreateFromFile("res/textures/grass.png");
			float aspectRatio = (float) Engine::Window::GetWidth() / Engine::Window::GetHeight();
			projectionmatrix = glm::perspective(3.1415f * 0.5f, aspectRatio, 0.1f, 100.0f) *
				glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));

			camera->RotateY(-35.0f);
			
		}




		void OnRender() const override {
			Engine::RenderCommand::ClearColorBuffer();
			tex->Bind();
			shader->Bind();
			shader->SetMat4("viewprojectionmatrix", projectionmatrix * camera->GetViewMatrix());
			vao->Bind();

			Engine::RenderCommand::DrawIndexed(ibo->GetIndexCount());
		}

		void OnUpdate(float timestep) override {
			glm::vec3 deltaPosition{0.0f};
			if (Engine::Input::IsKeyDown(Engine::Key::W)) {
				deltaPosition += camera->Forward();
			}else if (Engine::Input::IsKeyDown(Engine::Key::S)) {
				deltaPosition += camera->Backward();
			}

			if (Engine::Input::IsKeyDown(Engine::Key::A)) {
				deltaPosition += camera->Left();
			}else if (Engine::Input::IsKeyDown(Engine::Key::D)) {
				deltaPosition += camera->Right();
			}

			if (Engine::Input::IsKeyDown(Engine::Key::SPACE)) {
				deltaPosition += camera->Up();
			}else if (Engine::Input::IsKeyDown(Engine::Key::LEFT_SHIFT)) {
				deltaPosition += camera->Down();
			}

			if(glm::length(deltaPosition) > 0.00001f)
				camera->position += timestep * glm::normalize(deltaPosition) * 3.0f;

		}

		void OnResize(const Engine::WindowResizeEvent& e) {
			Engine::RenderCommand::SetViewport(0, 0, e.width, e.height);
			float aspectRatio = (float)e.width / e.height;
			projectionmatrix = glm::perspective(3.1415f * 0.5f, aspectRatio, 0.1f, 100.0f) *
				glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
		}

		void MouseMoved(const Engine::MouseMovedEvent& e) {
			camera->RotateX(-0.3f * e.deltaY);
			camera->RotateY(-0.3f * e.deltaX);
		}

		
		glm::mat4 projectionmatrix;
		std::shared_ptr<Engine::Shader> shader;
		std::shared_ptr<Engine::VertexArray> vao;
		std::shared_ptr<Engine::VertexBuffer> vbo;
		std::shared_ptr<Engine::IndexBuffer> ibo;
		std::shared_ptr<Engine::Texture> tex;
		std::shared_ptr<Engine::Camera> camera;
	};

}

Engine::Application* CreateApplication() {
	return (Engine::Application*) new Minecraft::App;
}
