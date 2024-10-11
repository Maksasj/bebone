#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

layout (location = 0) out vec4 outColor;

uniform mat4 transform;
uniform mat4 cam;

void main() {
	gl_Position = cam * transform * vec4(aPos, 1.0);
	outColor = aColor;
}