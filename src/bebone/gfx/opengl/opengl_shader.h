#ifndef _BEBONE_GFX_OPENGL_OPENGL_SHADER_H_
#define _BEBONE_GFX_OPENGL_OPENGL_SHADER_H_

#include "../gfx_backend.h"
#include "../shaders/shader_code.h"

#include "opengl_shader_properties.h"
#include "opengl_uniform_buffer_object.h"

namespace bebone::gfx {
    using namespace bebone::core;

    /// Opengl shader wrapper
    class GLShader : private core::NonCopyable {
        private:
            GLuint shader;
            GLShaderProperties properties;

            /*!
             * Checks if opengl shader is compiled successfully
             * @param shader - opengl shader
            */
            static void check_shader_compilation(const GLuint& shader);

        public:
            /*!
             * Default constructor
             * @param code - Shader code object
             * @param shader_type - Shader type
             * @param properties - Shader properties object
            */
            GLShader(const ShaderCode& code, const ShaderType& shader_type, const GLShaderProperties& properties = None);

            /*!
             * Default constructor
             * @param code - Shader string code
             * @param shader_type - Shader type
             * @param properties - Shader properties object
            */
            GLShader(const std::string& code, const ShaderType& shader_type, const GLShaderProperties& properties = None);
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
