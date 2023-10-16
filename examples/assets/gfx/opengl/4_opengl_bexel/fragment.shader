#version 450 core

layout (location = 0) out vec4 fragColor;

layout (location = 0) in vec2 texCoord;

layout (binding = 0) uniform sampler2D inTexture;

void main() {
    fragColor = texture(inTexture, texCoord);
}