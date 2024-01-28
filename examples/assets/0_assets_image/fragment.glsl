#version 450 core

layout (location = 0) out vec4 FragColor;

layout (location = 0) in vec3 ourColor;
layout (location = 1) in vec2 TexCoord;

layout (binding = 0) uniform sampler2D ourTexture;

void main() {
    FragColor = texture(ourTexture, TexCoord);
}