#version 400 core
in vec4 f_color;
in vec2 f_uv;
out vec4 color;
uniform sampler2D texture_sampler;
uniform float time;

void main() {
	color = texture(texture_sampler, f_uv) * abs(sin(time));
}
