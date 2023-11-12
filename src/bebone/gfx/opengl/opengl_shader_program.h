#ifndef _OPENGL_SHADER_PROGRAM_H_
#define _OPENGL_SHADER_PROGRAM_H_

#include "../gfx_backend.h"
#include "opengl_shader_properties.h"
#include "opengl_shader.h"

namespace bebone::gfx::opengl {
    using namespace bebone::core;

    class GLShaderProgram : private NonCopyable {
        private:
            GLuint id;
            GLShaderProperties m_properties;

            void create_shader_program(const GLShader& vertex, const GLShader& fragment);
            GLint get_uniform_location(const char* uniformName) const;

            static void check_program_linking(const GLuint& program);

        public:
            GLShaderProgram(const GLShader& vertex, const GLShader& fragment);

            void set_uniform(const char* uniformName, const i32& value) const;
            void set_uniform(const char* uniformName, const GLsizei& size, const i32* value) const;
            void set_uniform(const char* uniformName, const u32& value) const;
            void set_uniform(const char* uniformName, const f32& value) const;
            void set_uniform(const char* uniformName, const Mat4f& value) const;

            void bind_buffer(const char* uniformBufferName, const i32& binding, const GLUniformBufferObject& buffer) const;

            void enable();
            void destroy();
    };
}

#endif
