#include "app.h"
#include <GL/glew.h>
#include "shader.h"
#include "file_utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

GLuint vertexArray;
GLuint vertexBuffer;
GLuint indexBuffer;
GLuint program;
GLint mvp_matrix_location;
glm::mat4 projection_matrix;
glm::vec3 camera_position;
float rotation_x;
float rotation_y;

void onRender(float time, float delta_time) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);
	glBindVertexArray(vertexArray);
	
	glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f))
		* glm::rotate(glm::mat4(1.0f), time, glm::vec3(1.0f, 0.0f, 0.0f))
		* glm::rotate(glm::mat4(1.0f), 0.5f * time, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 view_matrix = glm::translate(glm::mat4(1.0f), -camera_position)
		* glm::rotate(glm::mat4(1.0f), -rotation_y, glm::vec3(0.0f, 1.0f, 0.0f))
		* glm::rotate(glm::mat4(1.0f), -rotation_x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 mvp_matrix = projection_matrix * view_matrix * model_matrix;
	glUniformMatrix4fv(mvp_matrix_location, 1, GL_FALSE, &mvp_matrix[0][0]);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
}

void onInit(int width, int height) {
	GLfloat vertices[] = {
		// front           red
		-0.5f, -0.5, 0.5f, 1.0f, 0.0f, 0.0f, 
		0.5f, -0.5, 0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5, 0.5f, 1.0f, 0.0f, 0.0f,
		-0.5f, 0.5, 0.5f, 1.0f, 0.0f, 0.0f,
		// back            green
		-0.5f, -0.5, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5, -0.5f, 0.0f, 1.0f, 0.0f,
		// bottom          blue
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
		// top			   yellow
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
		// left            
		-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
		// right
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
	};

	GLuint connectionOrder[] = {
		// front
		0, 1, 2, 0, 2, 3,
		// back
		4, 5, 6, 4, 6, 7,
		// bottom
		8, 9, 10, 8, 10, 11,
		// top
		12, 13, 14, 12, 14, 15,
		// left
		16, 17, 18, 16, 18, 19,
		// right
		20, 21, 22, 20, 22, 23
	};

	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(connectionOrder), connectionOrder, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, nullptr);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (const void*)(3 * sizeof(GLfloat)));
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	

	std::string vertex_source = utils::read_file("resources/vertex_shader.glsl");
	std::string fragment_source = utils::read_file("resources/fragment_shader.glsl");

	
	program = createShader(vertex_source.c_str(), fragment_source.c_str());
	mvp_matrix_location = glGetUniformLocation(program, "mvp_matrix");
	projection_matrix = glm::perspective(0.5f * 3.141f, (float)width / height, 0.01f, 1000.0f);
}


void onResize(int width, int height) {
	glViewport(0, 0, width, height);
	projection_matrix = glm::perspective(0.5f * 3.141f, (float) width / height, 0.01f, 1000.0f);
}