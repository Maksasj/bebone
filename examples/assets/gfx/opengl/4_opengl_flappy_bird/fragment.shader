#version 450 core

layout (location = 0) in vec2 texCoords;
layout (location = 0) out vec3 outColor;

layout (binding = 0) uniform sampler2D image;

void main() {
	outColor = texture(image, texCoords).rgb;
}