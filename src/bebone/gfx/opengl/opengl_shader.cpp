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
        glShaderSource(shader, 1, &source, NULL);
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

    void GLShaderProgram::enable() {
        glUseProgram(id);
    }

    void GLShaderProgram::destroy() {
        glDeleteProgram(id);
    }
}
