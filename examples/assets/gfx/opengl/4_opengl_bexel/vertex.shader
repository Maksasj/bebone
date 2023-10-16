#version 450 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoord;

layout (location = 0) out vec2 aTexCoord;

layout(binding = 0) uniform Transform {
    mat4 transform;
};

layout(binding = 1) uniform Camera {
    mat4 view;
    mat4 proj;
};

void main() {
	gl_Position = proj * view * transform * vec4(inPos, 1.0);
	aTexCoord = inTexCoord;
}