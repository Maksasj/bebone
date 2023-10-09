#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

layout (location = 0) out vec3 outColor;

layout(binding = 0) uniform Transform {
    mat4 translation;
    mat4 scale;
    mat4 rotation;
};

layout(binding = 1) uniform Camera {
    mat4 proj;
    mat4 view;
};

void main() {
	gl_Position = proj * view * translation * rotation * scale * vec4(aPos, 1.0);
	outColor = aColor;
}