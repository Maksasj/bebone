#include "spirv_shader_compiler.h"

namespace bebone::gfx {
    ShaderCode SpirVShaderCompiler::compile(const ShaderType& shader_type) {
        const auto target_shader_type = to_glslang(shader_type);

        // First we check if all shader source type match
        for(auto& shader_source : shader_sources)
            if(shader_type != shader_source.get_type()) {
                LOG_ERROR("Shader source type do not match with desired shader code target type");
                // throw std::runtime_error("shader source type do not match with desired shader code target type"); Todo
            }

        std::vector<const char*> raw_shader_sources;

        for(const auto& source : shader_sources)
            raw_shader_sources.push_back(source.get_shader_source().c_str());

        glslang::InitializeProcess();
        glslang::TShader shader(target_shader_type);

        shader.setStrings(raw_shader_sources.data(), raw_shader_sources.size());
        shader.setEntryPoint(default_entry_point.c_str());

        #if 0
            // Set environment input for Vulkan
            shader.setEnvInput(glslang::EShSource::EShSourceGlsl, target_shader_type, glslang::EShClient::EShClientVulkan, 100);

            // Set environment target for Vulkan SPIR-V
            shader.setEnvClient(glslang::EShClient::EShClientVulkan, glslang::EShTargetClientVersion::EShTargetVulkan_1_2);
            shader.setEnvTarget(glslang::EShTargetLanguage::EShTargetSpv, glslang::EShTargetLanguageVersion::EShTargetSpv_1_0);
        #else
            shader.setEnvInput(glslang::EShSource::EShSourceGlsl, target_shader_type, glslang::EShClient::EShClientOpenGL, 450);

            shader.setEnvClient(glslang::EShClient::EShClientOpenGL, glslang::EShTargetClientVersion::EShTargetOpenGL_450);
            shader.setEnvTarget(glslang::EShTargetLanguage::EShTargetSpv, glslang::EShTargetLanguageVersion::EShTargetSpv_1_0);
        #endif

        const int default_version = 100;
        EShMessages messages = (EShMessages)(EShMsgSpvRules | EShMsgVulkanRules);
        // EShMessages messages = (EShMessages)(EShMsgSpvRules);
        if (!shader.parse(GetDefaultResources(), default_version, false, messages)) {
            LOG_ERROR("Error in shader compilation: {}", shader.getInfoLog());

            glslang::FinalizeProcess();
            // throw std::runtime_error("Error in shader source"); Todo
        }

        glslang::TProgram program;
        program.addShader(&shader);

        // Todo take reflection there
        // program.getReflectionIndex

        if (!program.link(messages)) {
            LOG_ERROR("Error while linking shaders: {}", program.getInfoLog());
            glslang::FinalizeProcess();
            // throw std::runtime_error("Error while linking shaders"); Todo
        }

        glslang::TIntermediate *intermediate = program.getIntermediate(target_shader_type);
        if (!intermediate) {
            LOG_ERROR("Failed to get SPIR-V intermediate code.");
            glslang::FinalizeProcess();
            // throw std::runtime_error("Failed to get SPIR-V intermediate code"); Todo
        }

        // SpirV to be returned
        RawSpirVByteCode spirv_code;

        spv::SpvBuildLogger logger;
        glslang::SpvOptions spv_options;
        glslang::GlslangToSpv(*intermediate, spirv_code, &logger, &spv_options);

        glslang::FinalizeProcess();

        return ShaderCode(spirv_code, shader_type);
    }
}
