#ifndef _BEBONE_GFX_OPENGL_OPENGL_SHADER_H_
#define _BEBONE_GFX_OPENGL_OPENGL_SHADER_H_

#include "../gfx_backend.h"
#include "../shaders/shader_code.h"

#include "opengl_shader_properties.h"
#include "opengl_uniform_buffer_object.h"

namespace bebone::gfx::opengl {
    using namespace bebone::core;

    class GLShader : private core::NonCopyable {
        private:
            GLuint m_shader;
            GLShaderProperties m_properties;

            static void check_shader_compilation(const GLuint& shader);

        public:
            GLShader(const ShaderCode& code, const ShaderType& shaderType, const GLShaderProperties& properties = NONE);
            GLShader(const std::string& code, const ShaderType& shaderType, const GLShaderProperties& properties = NONE);
            ~GLShader();

            GLuint get_shader() const;
            const GLShaderProperties& get_properties() const;

            void destroy();
    };
}

#endif
