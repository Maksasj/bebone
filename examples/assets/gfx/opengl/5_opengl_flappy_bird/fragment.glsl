#version 450 core

layout (location = 0) in vec2 a_TexCoords;

out vec4 v_Color;

uniform sampler2D image;

void main() {
	v_Color = texture(image, a_TexCoords);
}