#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture.h"
#include <GL/glew.h>
#include "core/Logger.h"


Engine::Texture::Texture():
	texture_ID(0)
{
}

Engine::Texture::~Texture()
{
}

void Engine::Texture::Create()
{
	glGenTextures(1, &texture_ID);
}

void Engine::Texture::LoadImage(const std::string& path)
{

	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	

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

void Engine::Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, texture_ID);
}

void Engine::Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, texture_ID);
}
