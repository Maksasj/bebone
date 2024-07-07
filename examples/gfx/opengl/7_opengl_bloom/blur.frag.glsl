#version 450 core

layout (location = 0) out vec4 FragColor;

layout (location = 0) in vec2 texCoord;

uniform sampler2D image;

void main() {
	vec4 result = vec4(0.0f);

	for(int x = -5; x < 5; ++x) {
		for(int y = -5; y < 5; ++y) {
			vec2 offset = 5 * vec2(x/800.0, y/600.0);
			result += texture(image, texCoord + offset);
		}
	}

	FragColor = result * (1.0/50.0);
}