#version 450 core

layout (location = 0) in vec2 a_TexCoords;

layout (location = 0) out vec3 v_Color;

layout (binding = 0) uniform sampler2D image;

void main() {
	v_Color = texture(image, a_TexCoords).rgb;
}