#include "bebone/bebone.h"

#include <vector>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace bebone::gfx;
using namespace bebone::gfx::opengl;

const std::vector<GLfloat> vertices = {
    -0.5f, -0.5f, 0.0f, // left  
    0.5f, -0.5f, 0.0f, // right 
    0.0f,  0.5f, 0.0f  // top   
};

const std::vector<GLuint> indices = {
	0, 1, 2,
};

int main() {
    glfwInit();

    auto window = WindowFactory::create_window("1. OpenGL hello triangle example", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OPENGL);

	gladLoadGL();
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    ShaderCode vertexShaderCode(ShaderTypes::VERTEX_SHADER);
    ShaderCode fragmentShaderCode(ShaderTypes::FRAGMENT_SHADER);

    {   // Compiling glsl vertex shader code;
        ShaderCompiler shaderCompiler;
        
        shaderCompiler.add_shader_source(ShaderSource(read_file("examples/assets/gfx/opengl/1_opengl_hello_triangle/vertex.shader"), ShaderTypes::VERTEX_SHADER));
        vertexShaderCode = shaderCompiler.compile(ShaderTypes::VERTEX_SHADER);
    }

    std::cout << "poggers !\n";

    {   // Compiling glsl fragment shader code;
        ShaderCompiler shaderCompiler;
        
        shaderCompiler.add_shader_source(ShaderSource(read_file("examples/assets/gfx/opengl/1_opengl_hello_triangle/fragment.shader"), ShaderTypes::FRAGMENT_SHADER));
        fragmentShaderCode = shaderCompiler.compile(ShaderTypes::FRAGMENT_SHADER);
    }

    std::cout << "poggers !\n";

    GLShader vertexShader(vertexShaderCode, GL_VERTEX_SHADER);
    GLShader fragmentShader(fragmentShaderCode, GL_FRAGMENT_SHADER);
    GLShaderProgram shaderProgram(vertexShader, fragmentShader);

    vertexShader.destroy();
    fragmentShader.destroy();
    
    GLVertexArrayObject vao;
    vao.bind();

    GLVertexBufferObject vbo(vertices);
    GLElementBufferObject ebo(indices);

    vao.link_attributes(vbo, 0, 3, GL_FLOAT, 3 * (sizeof(float)), (void*)0);

    vao.unbind();
	vbo.unbind();
	ebo.unbind();

    while (!window->closing()) {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.enable();
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

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
