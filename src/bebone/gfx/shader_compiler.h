#ifndef _BEBONE_GFX_SHADER_COMPILER_H_
#define _BEBONE_GFX_SHADER_COMPILER_H_

#include <SPIRV/GlslangToSpv.h>
#include <glslang/Public/ShaderLang.h>
#include <glslang/Public/ResourceLimits.h>

#include <iostream>

/*
const char *vvvertexShaderSource = "#version 450 core\n"
                                "layout (location = 0) in vec3 aPos;\n"
                                "void main() {\n"
                                "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                "}\0";
const char *fffragmentShaderSource = "#version 450 core\n"
                                  "layout (location = 0) out vec4 FragColor;\n"
                                  "void main() {\n"
                                  "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                  "}\n\0";
*/

namespace bebone::gfx {
    class ShaderCompiler {
        public:
            static void compile_shader(const char *shaderSource, EShLanguage shaderType, std::vector<unsigned int> &spirvCode) {
                glslang::InitializeProcess();
                glslang::TShader shader(shaderType);
                shader.setStrings(&shaderSource, 1);
                
                #if 1
                    // Set environment input for Vulkan
                    shader.setEnvInput(glslang::EShSource::EShSourceGlsl, shaderType, glslang::EShClient::EShClientVulkan, 100);

                    // Set environment target for Vulkan SPIR-V
                    shader.setEnvClient(glslang::EShClient::EShClientVulkan, glslang::EShTargetClientVersion::EShTargetVulkan_1_2);
                    shader.setEnvTarget(glslang::EShTargetLanguage::EShTargetSpv, glslang::EShTargetLanguageVersion::EShTargetSpv_1_0);
                #else
                    shader.setEnvInput(glslang::EShSource::EShSourceGlsl, shaderType, glslang::EShClient::EShClientOpenGL, 450);
                    shader.setEnvClient(glslang::EShClient::EShClientOpenGL, glslang::EShTargetClientVersion::EShTargetOpenGL_450);
                    shader.setEnvTarget(glslang::EShTargetLanguage::EShTargetSpv, glslang::EShTargetLanguageVersion::EShTargetSpv_1_0);
                #endif

                const int defaultVersion = 100;
                EShMessages messages = (EShMessages)(EShMsgSpvRules | EShMsgVulkanRules);
                if (!shader.parse(GetDefaultResources(), defaultVersion, false, messages)) {
                    std::cerr << "Error in shader compilation:\n" << shader.getInfoLog() << std::endl;
                    std::cerr << "Error in shader source:\n" << shaderSource << std::endl;
                    glslang::FinalizeProcess();
                    throw std::runtime_error("Error in shader source");
                }

                glslang::TProgram program;
                program.addShader(&shader);

                // Todo take reflection there
                // program.getReflectionIndex

                if (!program.link(messages)) {
                    std::cerr << "Error while linking shaders:\n" << program.getInfoLog() << std::endl;
                    glslang::FinalizeProcess();
                    throw std::runtime_error("Error while linking shaders");
                }

                glslang::TIntermediate *intermediate = program.getIntermediate(shaderType);
                if (!intermediate) {
                    std::cerr << "Failed to get SPIR-V intermediate code." << std::endl;
                    glslang::FinalizeProcess();
                    throw std::runtime_error("Failed to get SPIR-V intermediate code");
                }

                spv::SpvBuildLogger logger;
                glslang::SpvOptions spvOptions;
                glslang::GlslangToSpv(*intermediate, spirvCode, &logger, &spvOptions);

                glslang::FinalizeProcess();
            }
    };
}

#endif
