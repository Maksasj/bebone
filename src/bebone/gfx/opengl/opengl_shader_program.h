#ifndef _BEBONE_GFX_OPENGL_OPENGL_SHADER_PROGRAM_H_
#define _BEBONE_GFX_OPENGL_OPENGL_SHADER_PROGRAM_H_

#include "../gfx_backend.h"
#include "opengl_shader_properties.h"
#include "opengl_shader.h"

namespace bebone::gfx::opengl {
    using namespace bebone::core;

    /// Shader Program
    class GLShaderProgram : private NonCopyable {
        private:
            GLuint id;
            GLShaderProperties m_properties;

            void create_shader_program(const GLShader& vertex, const GLShader& fragment);
            GLint get_uniform_location(const char* uniformName) const;

            static void check_program_linking(const GLuint& program);

        public:
            /*!
             * Creates shader program
             * @param vertex - vertex shader object. Can be created via GLShaderFactory
             * @param fragment - fragment shader object. Can be created via GLShaderFactory
             */
            GLShaderProgram(const GLShader& vertex, const GLShader& fragment);
            ~GLShaderProgram();

            /*!
             * glUniform1i
             * @param uniformName - uniform name from the shader
             * @param value - the value to be assigned to the uniform
             */
            void set_uniform(const char* uniformName, const i32& value) const;

            /*!
             * glUniform1iv
             * @param uniformName - uniform name from the shader
             * @param size - array size (not in bytes)
             * @param value - the value to be assigned to the uniform
             */
            void set_uniform(const char* uniformName, const GLsizei& size, const i32* value) const;

            /*!
             * glUniform1ui
             * @param uniformName - uniform name from the shader
             * @param value - the value to be assigned to the uniform
             */
            void set_uniform(const char* uniformName, const u32& value) const;

            /*!
             * glUniform1f
             * @param uniformName - uniform name from the shader
             * @param value - the value to be assigned to the uniform
             */
            void set_uniform(const char* uniformName, const f32& value) const;

            /*!
            * glUniform2f
            * @param uniformName - uniform name from the shader
            * @param value - the value to be assigned to the uniform
            */
            void set_uniform(const char* uniformName, const Vec2f& value) const;

            /*!
            * glUniform3f
            * @param uniformName - uniform name from the shader
            * @param value - the value to be assigned to the uniform
            */
            void set_uniform(const char* uniformName, const Vec3f& value) const;

            /*!
            * glUniform4f
            * @param uniformName - uniform name from the shader
            * @param value - the value to be assigned to the uniform
            */
            void set_uniform(const char* uniformName, const Vec4f& value) const;

            /*!
             * glUniformMatrix4fv
             * @param uniformName - uniform name from the shader
             * @param value - the value to be assigned to the uniform
             */
            void set_uniform(const char* uniformName, const Mat4f& value) const;

            /*!
            * Binds uniform buffer object to shader program
            * @param uniformBufferName - uniform buffer name
            * @param binding - uniform buffer binding
            * @param buffer - GLUniformBufferObject object
            */
            void bind_buffer(const char* uniformBufferName, const i32& binding, const GLUniformBufferObject& buffer) const;

            /// Enables shader program
            void enable();

            /// Destroys shader program. Calls automatically in the destructor
            void destroy();
    };
}

#endif
