#pragma once

#include <string>

namespace Engine {

	class Texture {

		uint32_t texture_ID;
		int width, height, nrChannels;
	
		

	public:
		Texture();
		~Texture();

		void Create();

		void LoadImage(const std::string& path);

		void Bind() const;
		void Unbind() const;

	};


}