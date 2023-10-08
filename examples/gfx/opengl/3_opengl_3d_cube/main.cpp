#include <vector>

#define OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
#define OMNI_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace bebone::gfx;
using namespace bebone::gfx::opengl;

const std::vector<GLfloat> vertices {
    // positions          // colors
    -0.5, -0.5,  0.5,   1.0f, 1.0f, 1.0f,
     0.5, -0.5,  0.5,   1.0f, 1.0f, 0.0f,
     0.5,  0.5,  0.5,   1.0f, 0.0f, 1.0f,
    -0.5,  0.5,  0.5,   1.0f, 0.0f, 0.0f,
    -0.5, -0.5, -0.5,   0.0f, 1.0f, 1.0f,
     0.5, -0.5, -0.5,   0.0f, 1.0f, 0.0f,
     0.5,  0.5, -0.5,   0.0f, 0.0f, 1.0f,
    -0.5,  0.5, -0.5,   0.0f, 0.0f, 0.0f
};

const std::vector<GLuint> indices {
    0, 1, 2, 2, 3, 0,
    1, 5, 6, 6, 2, 1,
    7, 6, 5, 5, 4, 7,
    4, 0, 3, 3, 7, 4,
    4, 5, 1, 1, 0, 4,
    3, 2, 6, 6, 7, 3
};

int main() {
    glfwInit();

    auto window = WindowFactory::create_window("3. OpenGL 3D cube example", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OPENGL);

	gladLoadGL();
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    GLShader vertexShader("examples/assets/gfx/opengl/3_opengl_3d_cube/vertex.shader", GL_VERTEX_SHADER);
    GLShader fragmentShader("examples/assets/gfx/opengl/3_opengl_3d_cube/fragment.shader", GL_FRAGMENT_SHADER);
    GLShaderProgram shaderProgram(vertexShader, fragmentShader);

    vertexShader.destroy();
    fragmentShader.destroy();
    
    GLVertexArrayObject vao;
    vao.bind();

    GLVertexBufferObject vbo(vertices);
    GLElementBufferObject ebo(indices);

    vao.link_attributes(vbo, 0, 3, GL_FLOAT, 6 * (sizeof(float)), (void*)0);
    vao.link_attributes(vbo, 1, 3, GL_FLOAT, 6 * (sizeof(float)), (void*)(3 * sizeof(float)));

    vao.unbind();
	vbo.unbind();
	ebo.unbind();

    Mat4f transform = Mat4f::translation(Vec3f(0, 0, 0));
    Mat4f scale = Mat4f::identity();
    
    Mat4f view = Mat4f::translation(Vec3f(0, 0, 5));
    Mat4f proj = Mat4f::perspective(1, window->get_aspect(), 0.1f, 100.0f);

    float t = 0;

    glEnable(GL_DEPTH_TEST);

    while (!window->closing()) {
        
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.enable();

        ++t;
        Mat4f rotation = trait_bryan_angle_yxz(Vec3f(t * 0.001f, t * 0.001f, 0.0f));

        shaderProgram.set_uniform("transform", transform);
        shaderProgram.set_uniform("scale", scale);
        shaderProgram.set_uniform("rotation", rotation);

        shaderProgram.set_uniform("view", view);
        shaderProgram.set_uniform("proj", proj);

        vao.bind();

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window->get_backend());
        glfwPollEvents();
    }

    vao.destroy();
    vbo.destroy();
    ebo.destroy();
    shaderProgram.destroy();

    glfwTerminate();
    return 0;
}
