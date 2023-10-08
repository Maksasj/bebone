#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 outColor;

uniform mat4 transform;
uniform mat4 scale;
uniform mat4 rotation;

uniform mat4 proj;
uniform mat4 view;

void main()
{
	gl_Position = proj * view * transform * rotation * scale * vec4(aPos, 1.0);
	outColor = aColor;
}