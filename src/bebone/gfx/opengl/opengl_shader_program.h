#ifndef _BEBONE_GFX_OPENGL_OPENGL_SHADER_PROGRAM_H_
#define _BEBONE_GFX_OPENGL_OPENGL_SHADER_PROGRAM_H_

#include "../gfx_backend.h"
#include "opengl_shader_properties.h"
#include "opengl_shader.h"

namespace bebone::gfx {
    using namespace bebone::core;

    /// Shader Program
    class GLShaderProgram : private NonCopyable {
        private:
            GLuint id;
            GLShaderProperties properties;

            void create_shader_program(const GLShader& vertex, const GLShader& fragment);
            GLint get_uniform_location(const char* uniform_name) const;

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
             * @param uniform_name - uniform name from the shader
             * @param value - the value to be assigned to the uniform
             */
            void set_uniform(const char* uniform_name, const i32& value) const;

            /*!
             * glUniform1iv
             * @param uniform_name - uniform name from the shader
             * @param size - array size (not in bytes)
             * @param value - the value to be assigned to the uniform
             */
            void set_uniform(const char* uniform_name, const GLsizei& size, const i32* value) const;

            /*!
             * glUniform1ui
             * @param uniform_name - uniform name from the shader
             * @param value - the value to be assigned to the uniform
             */
            void set_uniform(const char* uniform_name, const u32& value) const;

            /*!
             * glUniform1f
             * @param uniform_name - uniform name from the shader
             * @param value - the value to be assigned to the uniform
             */
            void set_uniform(const char* uniform_name, const f32& value) const;

            /*!
            * glUniform2f
            * @param uniform_name - uniform name from the shader
            * @param value - the value to be assigned to the uniform
            */
            void set_uniform(const char* uniform_name, const Vec2f& value) const;

            /*!
            * glUniform3f
            * @param uniform_name - uniform name from the shader
            * @param value - the value to be assigned to the uniform
            */
            void set_uniform(const char* uniform_name, const Vec3f& value) const;

            /*!
            * glUniform4f
            * @param uniform_name - uniform name from the shader
            * @param value - the value to be assigned to the uniform
            */
            void set_uniform(const char* uniform_name, const Vec4f& value) const;

            /*!
             * glUniformMatrix4fv
             * @param uniform_name - uniform name from the shader
             * @param value - the value to be assigned to the uniform
             */
            void set_uniform(const char* uniform_name, const Mat4f& value) const;

            /*!
            * Binds uniform buffer object to shader program
            * @param uniform_buffer_name - uniform buffer name
            * @param binding - uniform buffer binding
            * @param buffer - GLUniformBufferObject object
            */
            void bind_buffer(const char* uniform_buffer_name, const i32& binding, const GLUniformBufferObject& buffer) const;

            /// Enables shader program
            void enable();

            /// Destroys shader program. Calls automatically in the destructor
            void destroy();
    };
}

#endif
