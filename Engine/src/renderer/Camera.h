#pragma once
#include "glm/gtx/transform.hpp"
#include <memory>

namespace Engine {
	class Camera
	{
		glm::mat4 viewMatrix = glm::mat4(1.0f);

	public:
		static std::shared_ptr<Camera> Create();
		~Camera();

		
		glm::mat4 SetPosition(float x, float y, float z);
		glm::mat4 RotateX(float degree);
		glm::mat4 RotateY(float degree);
		glm::mat4 RotateZ(float degree);
		glm::mat4 GetViewMatrix();
	};

}