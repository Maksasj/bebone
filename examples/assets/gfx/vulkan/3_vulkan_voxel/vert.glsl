#version 450 core
#extension GL_EXT_nonuniform_qualifier : enable

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

layout (location = 0) out vec3 fragColor;

layout(binding = 0) uniform TransformUBO {
   mat4 translation;
   mat4 scale;
   mat4 rotation;
} transform[];

layout(binding = 1) uniform CameraUBO {
   mat4 view;
   mat4 proj;
} camera[];

layout( push_constant ) uniform Handles {
    int camera;
    int transform;
} handles;

void main() {
    mat4 translation = transform[handles.transform].translation;
    mat4 scale = transform[handles.transform].scale;
    mat4 rotation = transform[handles.transform].rotation;

    mat4 view = camera[handles.camera].view;
    mat4 proj = camera[handles.camera].proj;

    mat4 model = translation * rotation * scale;
    gl_Position = proj * view * model * vec4(position, 1.0);

    fragColor = color;
}
