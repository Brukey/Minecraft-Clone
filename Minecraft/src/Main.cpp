#include <Engine.h>
#include <core/Entrypoint.h>

#include "types/Block.h"
#include "types/Chunk.h"
#include "types/World.h"
#include <vector>

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

			world.Load();
			world.GetBlock({-1, 23, -19});

			camera = Engine::Camera::Create();

			float aspectRatio = (float) Engine::Window::GetWidth() / Engine::Window::GetHeight();
			projectionmatrix = glm::perspective(3.1415f * 0.5f, aspectRatio, 0.1f, 100.0f);

			camera->position = { -0.3f, 0, 0.0f };

			shader = Engine::Shader::CreateFromFile("res/shaders/Shader.glsl");
			uint32_t samplers[30];
			for (uint32_t i = 0; i < 30; i++)
				samplers[i] = i;
			shader->Bind();
			shader->SetIntArray("samplers", (int32_t*) samplers, 30);
			
		}




		void OnRender() const override {
			Engine::RenderCommand::ClearColorBuffer();
			shader->Bind();

			shader->SetMat4("viewprojectionmatrix", projectionmatrix * camera->GetViewMatrix());

			world.Render();
		}

		void OnUpdate(float timestep) override {
			glm::vec3 deltaPosition{0.0f};
			constexpr float maxSpeed = 9.0f;
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
				camera->position += timestep * glm::normalize(deltaPosition) * maxSpeed;

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
		
		mutable World world;
		std::shared_ptr<Engine::Shader> shader;
		std::shared_ptr<Engine::Camera> camera;
	};

}

Engine::Application* CreateApplication() {
	return (Engine::Application*) new Minecraft::App;
}
