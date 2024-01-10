#ifndef _BEBONE_GFX_OPENGL_OPENGL_SHADER_H_
#define _BEBONE_GFX_OPENGL_OPENGL_SHADER_H_

#include "../gfx_backend.h"
#include "../shaders/shader_code.h"

#include "opengl_shader_properties.h"
#include "opengl_uniform_buffer_object.h"

namespace bebone::gfx::opengl {
    using namespace bebone::core;

    /// Opengl shader wrapper
    class GLShader : private core::NonCopyable {
        private:
            GLuint m_shader;
            GLShaderProperties m_properties;

            /*!
             * Checks if opengl shader is compiled successfully
             * @param shader - opengl shader
            */
            static void check_shader_compilation(const GLuint& shader);

        public:
            /*!
             * Default constructor
             * @param code - Shader code object
             * @param shaderType - Shader type
             * @param properties - Shader properties object
            */
            GLShader(const ShaderCode& code, const ShaderType& shaderType, const GLShaderProperties& properties = NONE);

            /*!
             * Default constructor
             * @param code - Shader string code
             * @param shaderType - Shader type
             * @param properties - Shader properties object
            */
            GLShader(const std::string& code, const ShaderType& shaderType, const GLShaderProperties& properties = NONE);
            ~GLShader();

            /*!
             * Get OpenGL shader identifier
             * @return OpenGL shader identifier
            */
            GLuint get_shader() const;

            /*!
             * Function that returns opengl shader properties
             * @return - const reference to opengl shader properties
            */
            const GLShaderProperties& get_properties() const;

            /// Destroys OpenGL shader
            void destroy();
    };
}

#endif
