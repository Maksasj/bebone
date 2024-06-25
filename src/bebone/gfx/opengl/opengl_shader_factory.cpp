#include "opengl_shader_factory.h"

namespace bebone::gfx::opengl {
    std::string GLShaderFactory::read_file(const std::string& path) {
        std::ifstream file(path);
        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    bool GLShaderFactory::is_use_legacy_compiler(const GLShaderProperties& properties) {
        if (properties & GLShaderProperties::EnableUniforms)
            return true;

        // There we check if device supports SPIR-V binary shaders
        if (!GLExtensionChecker::available("GL_ARB_gl_spirv"))
            return true;

        return false;
    }

    GLShader GLShaderFactory::create_shader(const std::string& path, const ShaderType& shader_type, const GLShaderProperties& properties) {
        const auto source = read_file(path);

        if (is_use_legacy_compiler(properties))
            return GLShader(source, shader_type, properties);

        SpirVShaderCompiler shader_compiler;

        shader_compiler.add_shader_source(ShaderSource(source, shader_type));
        const auto code = shader_compiler.compile(shader_type);

        return GLShader(code, shader_type, properties);
    }
}
