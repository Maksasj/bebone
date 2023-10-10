#include "opengl_shader_factory.h"

namespace bebone::gfx::opengl {
    std::string GLShaderFactory::read_file(const std::string& path) {
        std::ifstream file(path);
        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    GLShader GLShaderFactory::create_shader(const std::string& path, const ShaderType& shaderType) {
        const auto source = read_file(path);

        if(GLExtensionChecker::available("GL_ARB_gl_spirv")) {
            SpirVShaderCompiler shaderCompiler;

            shaderCompiler.add_shader_source(ShaderSource(source, shaderType));
            const auto code = shaderCompiler.compile(shaderType);

            return GLShader(code, shaderType);
        }

        return GLShader(source, shaderType);
    }
}
