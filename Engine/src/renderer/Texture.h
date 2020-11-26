#pragma once

#include <string>
#include <memory>

namespace Engine {

	class Texture {

		uint32_t texture_ID;
		int width, height, nrChannels;
	
		

	public:
		Texture();
		~Texture();

		static std::shared_ptr<Texture> CreateFromFile(const char* path);
		

		void LoadImage(const std::string& path);

		void Bind(uint32_t slot = 0) const;
		void Unbind() const;

		inline uint32_t GetWidth() const { return width; }
		inline uint32_t GetHeight() const { return height; }
		inline uint32_t GetNumColorComponents() const { return nrChannels; }
	};


}