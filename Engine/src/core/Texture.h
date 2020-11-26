#pragma once
#include "EventManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


namespace Engine {

	class Texture {

		uint32_t texture_ID;
		int width, height, nrChannels;
	

	public:
		Texture();
		~Texture();

		void Create();

		void LoadImage(std::string path);

		void Bind();
		void Unbind();

	};


}