#include "opengl_shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

std::string get_file_contents(const char* fileName) {
	std::ifstream in(fileName, std::ios::binary);

	if (in) {
		std::string contents;

		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());

		in.close();
		return(contents);
	}

	throw(errno);
}

namespace bebone::gfx::opengl {
    GLShader::GLShader(const char* fileName, GLenum shaderType) {
        std::string contents = get_file_contents(fileName);
        const char* source = contents.c_str();

        shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);
    }

    GLuint GLShader::get_shader() const {
        return shader;
    }

    void GLShader::destroy() {
        glDeleteShader(shader);
    }

    GLShaderProgram::GLShaderProgram(const GLShader& vertex, const GLShader& fragment) {
        id = glCreateProgram();
        glAttachShader(id, vertex.get_shader());
        glAttachShader(id, fragment.get_shader());
        glLinkProgram(id);
    }

    void GLShaderProgram::set_uniform(const char* uniformName, GLint value) {
        GLint uniform = glGetUniformLocation(id, uniformName);
        glUniform1i(uniform, value);
    }

    void GLShaderProgram::set_uniform(const char* uniformName, GLuint value) {
        GLuint uniform = glGetUniformLocation(id, uniformName);
        glUniform1ui(uniform, value);
    }

    void GLShaderProgram::set_uniform(const char* uniformName, GLfloat value) {
        GLfloat uniform = glGetUniformLocation(id, uniformName);
        glUniform1f(uniform, value);
    }

    void GLShaderProgram::set_uniform(const char* uniformName, bebone::core::Mat4f value) {
        GLfloat uniform = glGetUniformLocation(id, uniformName);
        glUniformMatrix4fv(uniform, 1, GL_FALSE, value.e);
    }

    void GLShaderProgram::enable() {
        glUseProgram(id);
    }

    void GLShaderProgram::destroy() {
        glDeleteProgram(id);
    }
}
