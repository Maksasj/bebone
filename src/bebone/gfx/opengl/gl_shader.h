#ifndef _BEBONE_GFX_OPENGL_SHADER_H_
#define _BEBONE_GFX_OPENGL_SHADER_H_

#include <iostream>
#include <vector>

#include "../gfx_backend.h"
#include "../i_shader.h"

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

namespace bebone::gfx {
    class GLShader : public IShader {
        private:
            unsigned int shaderProgram;

        public:
            GLShader(std::vector<unsigned int>& spirvCodeVertex) {
                // unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
                // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
                // glCompileShader(vertexShader);

                int numFormats = 0;
                glGetIntegerv(GL_NUM_SHADER_BINARY_FORMATS, &numFormats);
                std::vector<GLint> binaryFormats(numFormats);
                glGetIntegerv(GL_PROGRAM_BINARY_FORMATS, binaryFormats.data());

                for (GLint supportedFormat : binaryFormats) {
                    if (supportedFormat == GL_SHADER_BINARY_FORMAT_SPIR_V) {
                        std::cout << "suported !\n";
                    }
                }

                unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
                std::cout << "Before binary\n";
                glShaderBinary(1, &vertexShader, GL_SHADER_BINARY_FORMAT_SPIR_V, spirvCodeVertex.data(), spirvCodeVertex.size() * sizeof(unsigned int));
                
                std::cout << "After binary\n";
                glSpecializeShader(vertexShader, "main", 0, nullptr, nullptr);
                // std::cout << "After binary\n";
                

                int success;
                char infoLog[512];
                // glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
                // if (!success) {
                //     glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                //     std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
                // }





                // unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                // glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
                // glCompileShader(fragmentShader);
// 
                // glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
                // if (!success)
                // {
                //     glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
                //     std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
                // }

                shaderProgram = glCreateProgram();
                glAttachShader(shaderProgram, vertexShader);
                // glAttachShader(shaderProgram, fragmentShader);
                glLinkProgram(shaderProgram);

                glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
                if (!success) {
                    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
                    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
                }
                glDeleteShader(vertexShader);
                // glDeleteShader(fragmentShader);
            }   

            void compile() override {
                glUseProgram(shaderProgram);
            }   

            void activate() const override {
                glUseProgram(shaderProgram);
            }   

            void terminate() const override {
                glDeleteProgram(shaderProgram);
            }
    };
}
#endif
