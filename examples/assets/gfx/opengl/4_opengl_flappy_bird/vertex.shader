#version 450 core

layout (location = 0) in vec4 vertex;

out vec2 TexCoords;

layout (binding = 0) uniform Matrices {
    mat4 model;
    mat4 projection;
};

void main() {
	TexCoords = vertex.zw;
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}