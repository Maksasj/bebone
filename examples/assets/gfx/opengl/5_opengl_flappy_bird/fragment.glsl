#version 450 core

layout (location = 0) in vec2 a_TexCoords;
layout (location = 1) in int a_TextureUnit;

layout (location = 0) out vec4 v_Color;

uniform sampler2D u_Textures[32];

void main() {
	v_Color = texture(u_Textures[a_TextureUnit], a_TexCoords);
}