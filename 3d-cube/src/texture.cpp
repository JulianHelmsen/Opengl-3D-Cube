#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


GLuint loadTextureFromDisc(const char* path) {
	GLuint texture;
	glGenTextures(1 , &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	int width;
	int height;
	int comp;
	unsigned char* data = stbi_load(path, &width, &height, &comp, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	return texture;
}