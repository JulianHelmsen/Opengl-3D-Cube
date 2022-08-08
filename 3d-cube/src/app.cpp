#include "app.h"
#include <GL/glew.h>
#include "shader.h"
#include "file_utils.h"

GLuint vertexArray;
GLuint vertexBuffer;
GLuint indexBuffer;
GLuint program;

void onRender(float time, float delta_time) {
	glUseProgram(program);
	glBindVertexArray(vertexArray);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void onInit(int width, int height) {
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


	std::string vertex_source = utils::read_file("resources/vertex_shader.glsl");
	std::string fragnent_source = utils::read_file("resources/fragment_shader.glsl");

	printf("%s\n", vertex_source.c_str());
	
	program = createShader(vertex_source.c_str(), fragnent_source.c_str());
}