#version 450 core

layout (location = 0) out vec4 FragColor;

layout (location = 0) in vec2 texCoord;

layout (binding = 0) uniform sampler2D image;
layout (binding = 1) uniform sampler2D blured;

void main() {
	vec4 fragment = texture(image, texCoord);
	vec4 bloom = texture(blured, texCoord);

	vec4 color = fragment + bloom;

	float exposure = 0.8f;
	vec4 toneMapped = vec4(1.0) - exp(-color * exposure);

	float gamma = 1.0f;

	FragColor = pow(toneMapped, vec4(1.0f / gamma));
}