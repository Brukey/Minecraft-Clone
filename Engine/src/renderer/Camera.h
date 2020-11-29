#pragma once
#include "glm/gtx/transform.hpp"
#include <memory>

namespace Engine {
	class Camera
	{


	public:
		static std::shared_ptr<Camera> Create();
		~Camera();

		
		void SetPosition(float x, float y, float z);
		void RotateX(float degree);
		void RotateY(float degree);
		void RotateZ(float degree);
		glm::mat4 GetViewMatrix();

		glm::vec3 Forward() const;
		glm::vec3 Up() const;
		glm::vec3 Right() const;
		inline glm::vec3 Backward() const {return -Forward();}
		inline glm::vec3 Down() const { return -Up(); }
		inline glm::vec3 Left() const { return -Right(); }

		glm::vec3 position{ 0.0f };
		glm::vec3 rotation{ 0.0f };
	};

}