#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
out vec4 f_color;
uniform mat4 mvp_matrix;

void main() {
	gl_Position = mvp_matrix * vec4(position, 1.0);
	f_color = vec4(color, 1.0);
}