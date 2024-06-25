#ifndef _BEBONE_GFX_OPENGL_OPENGL_SHADER_FACTORY_H_
#define _BEBONE_GFX_OPENGL_OPENGL_SHADER_FACTORY_H_

#include "../shaders/shader_type.h"

#include "../shaders/spirv_shader_compiler.h"

#include "opengl_shader_properties.h"
#include "opengl_extension_checker.h"
#include "opengl_shader.h"

namespace bebone::gfx::opengl {
    /// This class is used to create shaders
    class GLShaderFactory {
        private:
            static std::string read_file(const std::string& path);
            static bool is_use_legacy_compiler(const GLShaderProperties& properties);

        public:
            GLShaderFactory() = delete;

            /*!
             * Creates shader object from the specified file and parameters
             * @param path - path to the glsl shader file
             * @param shader_type - specifies the shader type (vertex or fragment)
             * @param properties - specifies other shader properties, like enabling uniforms
             * @return shader object
             */
            static GLShader create_shader(const std::string& path, const ShaderType& shader_type, const GLShaderProperties& properties = None);
    };
}

#endif
