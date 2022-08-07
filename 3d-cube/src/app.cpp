#include "app.h"
#include <GL/glew.h>
#include "shader.h"
#include "file_utils.h"

GLuint vertexArray;
GLuint vertexBuffer;
GLuint program;

void onRender() {
	glUseProgram(program);
	glBindVertexArray(vertexArray);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
}

void onInit() {
	GLfloat vertices[] = {0.5f, 0.5f, 0.0f, -0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f};
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	glGenBuffers(100, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, nullptr);


	std::string vertex_source = utils::read_file("resources/vertex_shader.glsl");
	std::string fragnent_source = utils::read_file("resources/fragment_shader.glsl");

	printf("%s\n", vertex_source.c_str());
	
	program = createShader(vertex_source.c_str(), fragnent_source.c_str());
}