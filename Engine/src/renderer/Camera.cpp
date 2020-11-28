#include "Camera.h"

std::shared_ptr<Engine::Camera> Engine::Camera::Create() {
	std::shared_ptr<Engine::Camera> camera = std::make_shared<Engine::Camera>();

	return camera;
}

Engine::Camera::~Camera()
{
}


glm::mat4 Engine::Camera::SetPosition(float x, float y, float z)
{
	return viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}

glm::mat4 Engine::Camera::RotateX(float degree)
{
	return viewMatrix = glm::rotate(glm::mat4(1.0f), degree, glm::vec3(1.0f, 0.0f, 0.0f) );
}

glm::mat4 Engine::Camera::RotateY(float degree)
{
	return viewMatrix = glm::rotate(glm::mat4(1.0f), degree, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Engine::Camera::RotateZ(float degree)
{
	return viewMatrix = glm::rotate(glm::mat4(1.0f), degree, glm::vec3(0.0f, 0.0f, 1.0f));
}


glm::mat4 Engine::Camera::GetViewMatrix()
{
	return viewMatrix;
}
