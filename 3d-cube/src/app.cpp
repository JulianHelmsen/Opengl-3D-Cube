#include "app.h"
#include <GL/glew.h>
#include "shader.h"

GLuint vertexArray;
GLuint vertexBuffer;
GLuint indexBuffer;
GLuint program;

void onRender() {
	glUseProgram(program);
	glBindVertexArray(vertexArray);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void onInit() {
	GLfloat vertices[] = {0.5f, 0.5f, 0.0f, -0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f};
	GLuint connectionOrder[] = { 1, 0, 2, 1, 2, 3 };
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(connectionOrder), connectionOrder, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, nullptr);

	const char* vs_source_code = ""
		"#version 400 core\n"
		"\n"
		"layout(location = 0) in vec3 position;"
		"void main() {\n"
		"gl_Position = vec4 (position, 1.0);"
		"}";

	const char* fs_source_code = ""
		"#version 400 core\n"
		"\n"
		"out vec4 color;"
		"void main() {\n"
		"color = vec4(0.0, 0.0, 1.0, 1.0);"
		"}";
	
	program = createShader(vs_source_code, fs_source_code);
}