#version 450 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoords;
layout (location = 2) in float a_TextureUnit;

layout (location = 0) out vec2 v_TexCoords;
layout (location = 1) out flat float v_TextureUnit;

uniform mat4 u_Model;
uniform mat4 u_Projection;

void main() {
	v_TexCoords = a_TexCoords;
    v_TextureUnit = a_TextureUnit;
    gl_Position = u_Projection * u_Model * vec4(a_Position, 1.0);
}