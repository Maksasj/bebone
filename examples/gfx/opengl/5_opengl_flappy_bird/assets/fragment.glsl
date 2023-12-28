#version 450 core

layout (location = 0) in vec2 a_TexCoords;
layout (location = 1) in float a_TextureUnit;

layout (location = 0) out vec4 v_Color;

uniform sampler2D u_Textures[32];

void main() {
	int index = int(a_TextureUnit);

	vec4 color = texture(u_Textures[index], a_TexCoords);

	if (color.a == 0.0)
		discard;

	v_Color = color;
}