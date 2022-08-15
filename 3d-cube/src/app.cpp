#include "app.h"
#include <GL/glew.h>
#include "shader.h"
#include "file_utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "input.h"
#include "texture.h"

GLuint vertexArray;
GLuint vertexBuffer;
GLuint indexBuffer;
GLuint program;
GLuint texture;
GLint mvp_matrix_location;
glm::mat4 projection_matrix;
glm::vec3 camera_position;
float rotation_x;
float rotation_y = 3.1415f * 0.25f;

void onRender(float time, float delta_time) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);
	glBindVertexArray(vertexArray);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f))
		* glm::rotate(glm::mat4(1.0f), 0.0f * time, glm::vec3(1.0f, 0.0f, 0.0f))
		* glm::rotate(glm::mat4(1.0f), 0.0f * 0.5f * time, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 view_rotation_matrix = glm::rotate(glm::mat4(1.0f), rotation_y, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), rotation_x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 view_matrix = glm::inverse(glm::translate(glm::mat4(1.0f), camera_position)
		* view_rotation_matrix);
	glm::mat4 mvp_matrix = projection_matrix * view_matrix * model_matrix;
	glUniformMatrix4fv(mvp_matrix_location, 1, GL_FALSE, &mvp_matrix[0][0]);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);


	constexpr glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
	constexpr glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

	glm::vec3 camera_forward = glm::vec3(view_rotation_matrix * glm::vec4(forward, 0.0f));
	glm::vec3 camera_right = glm::vec3(view_rotation_matrix * glm::vec4(right, 0.0f));

	camera_forward.y = 0.0f;

	float delta_x, delta_y;

	input::getMouseDelta(&delta_x, &delta_y);
	rotation_x += delta_y * 0.001f;
	rotation_y -= delta_x * 0.001f;



	if (input::isButtonPressed('W'))
		camera_position += delta_time * camera_forward;
	if (input::isButtonPressed('S'))
		camera_position -= delta_time * camera_forward;
	if (input::isButtonPressed('D'))
		camera_position += delta_time * camera_right;
	if (input::isButtonPressed('A'))
		camera_position -= delta_time * camera_right;
	if (input::isButtonPressed(' '))
		camera_position.y += delta_time;
	if (input::isButtonPressed(GLFW_KEY_LEFT_SHIFT))
		camera_position.y -= delta_time;
	
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

	GLuint texture = loadTextureFromDisc("recources/shine_sprite_image.jpg");

}


void onResize(int width, int height) {
	glViewport(0, 0, width, height);
	projection_matrix = glm::perspective(0.5f * 3.141f, (float) width / height, 0.01f, 1000.0f);
}