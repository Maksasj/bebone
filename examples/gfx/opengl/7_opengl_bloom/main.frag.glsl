#version 450 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 invertedFragColor;

layout (location = 0) in vec4 outColor;

void main() {
	invertedFragColor = vec4(vec3(outColor.x + outColor.y + outColor.z / 3.0), 1.0);
	FragColor = outColor;
}