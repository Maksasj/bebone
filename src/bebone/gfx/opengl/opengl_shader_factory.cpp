#include "opengl_shader_factory.h"

namespace bebone::gfx::opengl {
    std::string GLShaderFactory::read_file(const std::string& path) {
        std::ifstream file(path);
        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    GLShader GLShaderFactory::create_shader(const std::string& path, const ShaderType& shaderType, const GLShaderProperties& propeties) {
        const auto source = read_file(path);

        auto useLegacyCompiler = false;

        if(propeties & GLShaderProperties::ENABLE_UNIFORMS)
            useLegacyCompiler = true;

        // There we check if device supports spirv binary shaders
        if(!GLExtensionChecker::available("GL_ARB_gl_spirv"))
            useLegacyCompiler = true;

        if(useLegacyCompiler)
            return GLShader(source, shaderType, propeties);

        SpirVShaderCompiler shaderCompiler;

        shaderCompiler.add_shader_source(ShaderSource(source, shaderType));
        const auto code = shaderCompiler.compile(shaderType);

        return GLShader(code, shaderType, propeties);
    }
}
