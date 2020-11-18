#pragma once


namespace Engine {

	class Application {

		void Start();
		virtual void OnStart() = 0;
		virtual void OnUpdate(float timestep) {}
	};
}
