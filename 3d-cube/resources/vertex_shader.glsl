#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 uv;

out vec4 f_color;
out vec2 f_uv;
out vec3 f_position;
uniform mat4 vp_matrix;
uniform mat4 model_matrix;

void main() {
	vec4 world_position = model_matrix * vec4(position, 1.0);
	gl_Position = vp_matrix * world_position;
	f_color = vec4(color, 1.0);
	f_uv = uv;
	f_position = world_position.xyz;
}