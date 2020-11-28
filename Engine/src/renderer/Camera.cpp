#include "Camera.h"

std::shared_ptr<Engine::Camera> Engine::Camera::Create() {
	std::shared_ptr<Engine::Camera> camera = std::make_shared<Engine::Camera>();

	return camera;
}

Engine::Camera::~Camera()
{
}


void Engine::Camera::SetPosition(float x, float y, float z)
{
	position = glm::vec3(x, y, z);
}

void Engine::Camera::RotateX(float degree)
{
	rotation.x += glm::radians(degree);
}

void Engine::Camera::RotateY(float degree)
{
	rotation.y += glm::radians(degree);
}

void Engine::Camera::RotateZ(float degree)
{
	rotation.z += glm::radians(degree);
}

glm::mat4 Engine::Camera::GetViewMatrix()
{
	glm::mat4 viewmatrix = glm::translate(glm::mat4(1.0f), position) * 
		glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) * 
		glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	return glm::inverse(viewmatrix);
}
