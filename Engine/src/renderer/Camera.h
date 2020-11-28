#pragma once
#include "glm/gtx/transform.hpp"
#include <memory>

namespace Engine {
	class Camera
	{
		glm::vec3 position{ 0.0f };
		glm::vec3 rotation{ 0.0f };

	public:
		static std::shared_ptr<Camera> Create();
		~Camera();

		
		void SetPosition(float x, float y, float z);
		void RotateX(float degree);
		void RotateY(float degree);
		void RotateZ(float degree);
		glm::mat4 GetViewMatrix();
	};

}