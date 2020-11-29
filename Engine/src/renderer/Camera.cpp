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
	rotation.x = fmax(-3.1415f * 0.5f, fmin(rotation.x, 3.141f * 0.5f));
}

void Engine::Camera::RotateY(float degree)
{
	rotation.y += glm::radians(degree);
}

void Engine::Camera::RotateZ(float degree)
{
	rotation.z += glm::radians(degree);
}

glm::vec3 Engine::Camera::Forward() const {
	glm::vec3 forward{ 0.0f, 0.0f, -1.0f };

	glm::vec4 newDirection = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(forward, 1.0f);
	return glm::vec3(newDirection);
}

glm::vec3 Engine::Camera::Up() const {
	return glm::vec3{ 0.0f, 1.0f, 0.0f };
}

glm::vec3 Engine::Camera::Right() const {
	glm::vec3 right{ 1.0f, 0.0f, 0.0f };

	glm::vec4 newDirection = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(right, 1.0f);
	return glm::vec3(newDirection);
}


glm::mat4 Engine::Camera::GetViewMatrix()
{
	glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 rotation = rotationZ * rotationY * rotationX;
	glm::mat4 viewmatrix = glm::translate(glm::mat4(1.0f), position) * rotation;
	return glm::inverse(viewmatrix);
}
