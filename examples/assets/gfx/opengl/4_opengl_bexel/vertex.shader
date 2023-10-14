#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

layout (location = 0) out vec3 outColor;

layout(binding = 0) uniform Transform {
    mat4 transform;
};

layout(binding = 1) uniform Camera {
    mat4 view;
    mat4 proj;
};

void main() {
	gl_Position = proj * view * transform * vec4(aPos, 1.0);
	outColor = aColor;
}