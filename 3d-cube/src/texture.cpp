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
	return texture;
}