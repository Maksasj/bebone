#ifndef _BEBONE_GFX_SHADER_COMPILER_H_
#define _BEBONE_GFX_SHADER_COMPILER_H_

#include "shader_code.h"
#include "shader_source.h"

namespace bebone::gfx {
    class ShaderCompiler {
        private:
            std::vector<ShaderSource> m_shaderSources;

        public:
            void add_shader_source(const ShaderSource& p_shaderSource) {
                m_shaderSources.push_back(p_shaderSource);
            }

            void clear_shader_source() {
                m_shaderSources.clear();
            }

            ShaderCode compile(const ShaderType& p_shaderType) {
                const EShLanguage targetShaderType = p_shaderType.to_glslang();

                // First we check if all shader source type match
                for(auto& shaderSource : m_shaderSources) {
                    if(p_shaderType != shaderSource.get_type())
                        throw std::runtime_error("shader source type do not match with desired shader code target type");
                }

                const size_t shaderSourcesSize = m_shaderSources.size();
                std::vector<char*> rawShaderSources(shaderSourcesSize);

                for(size_t i = 0; i < shaderSourcesSize; ++i) {
                    auto& shaderSource = m_shaderSources[i];
                    auto& shaderSourceStr = shaderSource.get_shader_source();

                    rawShaderSources[i] = new char[sizeof(u8) * shaderSourceStr.size()];
                    std::strcpy(rawShaderSources[i], shaderSourceStr.data());
                }

                glslang::InitializeProcess();
                glslang::TShader shader(targetShaderType);
                shader.setStrings(rawShaderSources.data(), 1);
                shader.setEntryPoint("main");
                
                #if 1
                    // Set environment input for Vulkan
                    shader.setEnvInput(glslang::EShSource::EShSourceGlsl, targetShaderType, glslang::EShClient::EShClientVulkan, 100);

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
                    // std::cerr << "Error in shader source:\n" << shaderSource << std::endl;
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

                glslang::TIntermediate *intermediate = program.getIntermediate(targetShaderType);
                if (!intermediate) {
                    std::cerr << "Failed to get SPIR-V intermediate code." << std::endl;
                    glslang::FinalizeProcess();
                    throw std::runtime_error("Failed to get SPIR-V intermediate code");
                }

                // SpirV to be returned
                RawSpirVByteCode spirVCode;

                spv::SpvBuildLogger logger;
                glslang::SpvOptions spvOptions;
                glslang::GlslangToSpv(*intermediate, spirVCode, &logger, &spvOptions);

                glslang::FinalizeProcess();

                // Cleanup
                for(size_t i = 0; i < shaderSourcesSize; ++i) {
                    delete [] rawShaderSources[i];
                }

                return ShaderCode(spirVCode, p_shaderType);
            }
    };
}

#endif
