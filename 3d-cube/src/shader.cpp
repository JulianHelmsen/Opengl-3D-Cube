#include "shader.h"
#include <GL/glew.h>

unsigned int createShader(const char* vertexShader, const char* fragmentShader) {

	GLuint program = glCreateProgram();
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
}