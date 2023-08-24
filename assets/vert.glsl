#version 450 core
#extension GL_EXT_nonuniform_qualifier : enable

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 inTexCoord;

layout (location = 0) out vec3 fragColor;
layout (location = 1) out vec2 fragTexCoord;

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
    uint transform;
    uint camera;
    float frame;
} handles;

float angle = handles.frame;

mat4 rotZ = mat4(
    cos(angle), -sin(angle), 0, 0,
    sin(angle), cos(angle), 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
);

mat4 rotX = mat4(
    1, 0, 0, 0,
    0, cos(angle), -sin(angle), 0,
    0, sin(angle), cos(angle), 0,
    0, 0, 0, 1
);

mat4 rotY = mat4(
    cos(angle), 0, sin(angle), 0,
    0, 1, 0, 0,
    -sin(angle), 0, cos(angle), 0,
    0, 0, 0, 1
);

mat4 ortographic(float right, float left, float bottom, float top, float near, float far) {
    return mat4(
        2.0f / (right - left), 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f / (bottom - top), 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f / (far - near), 0.0f,
        - (right + left) / (right - left), - (bottom + top) / (bottom - top), near / (near - far), 1.0f
    );
}

mat4 perspective(float fovy, float aspect, float near, float far) {
    float tanHalfFovy = tan(fovy / 2.f);

    return mat4(
        1.f / (aspect * tanHalfFovy), 0.0f, 0.0f, 0.0f,
        0.0f, 1.f / (tanHalfFovy), 0.0f, 0.0f,
        0.0f, 0.0f, far / (far - near), -(far * near) / (far - near),
        0.0f, 0.0f, 1.0f, 0.0f
    );
}


void main() {
    // mat4 proj = camera[handles.camera].proj;
    // mat4 view = camera[handles.camera].view;

    // mat4 proj = transpose(ortographic(2.0, -2.0, 2.0, -2.0, -2.0, 2.0));
    mat4 proj = transpose(perspective(1.0472, 8.0/6.0, 0.1, 10.0));

    // mat4 translation = transform[handles.transform].translation;
    // mat4 scale = transform[handles.transform].scale;
    // mat4 rotation = transform[handles.transform].rotation;

    mat4 translation = mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0, // <--- moved Y cord
        0.0, 0.0, 1.0, 2.5,
        0.0, 0.0, 0.0, 1.0
    );

    mat4 scale = mat4(
        0.3, 0.0, 0.0, 0.0,
        0.0, 0.3, 0.0, 0.0,
        0.0, 0.0, 0.3, 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    mat4 model = transpose(scale * rotX * rotY * translation);
    gl_Position = proj * model * vec4(position, 1.0);

    fragColor = color;
    fragTexCoord = inTexCoord;
}