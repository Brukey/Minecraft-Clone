#pragma once

#include <thread>

namespace Engine {

	class Application {
	public:
		void Start();
		
		virtual void OnStart() = 0;
		virtual void OnUpdate(float timestep) {}
		void OnRender() const;
		void OnClose();
		void Run();


	private:
		void UpdateThread();

	private:
		std::thread m_updateThread;
		bool m_running;
		

	};
}
