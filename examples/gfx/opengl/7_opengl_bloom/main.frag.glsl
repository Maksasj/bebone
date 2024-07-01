#version 450 core

layout (location = 0) out vec4 FragColor;

layout (location = 0) in vec4 outColor;

void main() {
	FragColor = outColor;
}