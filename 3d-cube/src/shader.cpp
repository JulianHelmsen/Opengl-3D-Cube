#include "shader.h"
#include <GL/glew.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

unsigned int createShader(const char* sourceVertexShader, const char* sourceFragmentShader) {

	GLuint program = glCreateProgram();
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	GLint vertex_source_length = strlen(sourceVertexShader);
	GLint fragment_source_length = strlen(sourceFragmentShader);
	glShaderSource(vertex_shader, 1, &sourceVertexShader, &vertex_source_length);
	glShaderSource(fragment_shader, 1, &sourceFragmentShader, &fragment_source_length);
	glCompileShader(vertex_shader);
	glCompileShader(fragment_shader);

	GLint is_compiled;

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &is_compiled);
	if (!is_compiled) {
		GLint info_log_length;
		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &info_log_length);
		GLchar* compile_error_str = (GLchar*) malloc(info_log_length * sizeof(GLchar));
		
		glGetShaderInfoLog(vertex_shader, info_log_length, &info_log_length, compile_error_str);
		printf("Compile error with vertex shader: %s\n", compile_error_str);
	}

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &is_compiled);
	if (!is_compiled) {
		GLint info_log_length;
		glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &info_log_length);
		GLchar* compile_error_str = (GLchar*) malloc(info_log_length * sizeof(GLchar));
		
		glGetShaderInfoLog(fragment_shader, info_log_length, &info_log_length, compile_error_str);
		printf("Compile error with fragment shader: %s\n", compile_error_str);
		free(compile_error_str);
	}
	
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	GLint is_linked;
	glGetProgramiv(program, GL_LINK_STATUS, &is_linked);
	if (!is_linked) {
		GLint info_log_length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		GLchar* link_error_str = (GLchar*) malloc(info_log_length * sizeof(GLchar));
		glGetProgramInfoLog(program, info_log_length, &info_log_length, link_error_str);
		printf("Link error: %s\n", link_error_str);
		free(link_error_str);
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return program;
}