#version 400 core

in vec4 f_color;
in vec2 f_uv;
in vec3 f_position;
out vec4 color;
uniform sampler2D texture_sampler;
uniform float time;

void main() {
	color = texture(texture_sampler, f_uv);

}
