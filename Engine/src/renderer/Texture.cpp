#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture.h"
#include <GL/glew.h>
#include "core/Logger.h"

namespace Engine {

	std::shared_ptr<Texture> Texture::CreateFromFile(const char* path) {
		stbi_set_flip_vertically_on_load(true);
		std::shared_ptr<Texture> texture = std::make_shared<Texture>();
		texture->LoadImage(path);
		return texture;
	}

	Texture::Texture()
	{
		glGenTextures(1, &texture_ID);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &texture_ID);
	}



	void Texture::LoadImage(const std::string& path)
	{

		stbi_set_flip_vertically_on_load(true);

		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

		Bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			LOG("Could not load image. %s, %d", "asd", 5);
		}


		stbi_image_free(data);
	}

	void Texture::Bind(uint32_t slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, texture_ID);
	}

	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}
