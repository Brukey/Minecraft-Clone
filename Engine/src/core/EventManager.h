#pragma once

#include <stdint.h>
#include <functional>
#include <vector>


namespace Engine {

	struct WindowCloseEvent {};

	struct WindowResizeEvent {
		uint32_t width;
		uint32_t height;
	};

	struct KeyPressedEvent {
		uint32_t keycode;
	};

	struct KeyReleasedEvent {
		uint32_t keycode;
	};


	class EventManager {
	public:
		template<typename T>
		using Func = std::function<void(const T&)>;

		template<typename T>
		static void Subscribe(Func<T> callback) {
			std::vector<Func<T>>& subscribed = GetSubscribeList<T>();
			subscribed.push_back(callback);
		}


		template<typename T>
		static void Publish(const T& event) {
			std::vector<Func<T>>& subscribed = GetSubscribeList<T>();
			for (Func<T>& callback : subscribed) {
				callback(event);
			}
		}


	private:
		template<typename T>
		constexpr static std::vector<Func<T>>& GetSubscribeList() {
			static std::vector<Func<T>> subscribed;
			return subscribed;
		}
	};
}