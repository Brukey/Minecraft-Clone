#pragma once


namespace Engine {

	class Application {
	public:
		void Start();
		
		virtual void OnStart() = 0;
		virtual void OnUpdate(float timestep) {}
		void OnClose();
		void Run();
	private:
	};
}
