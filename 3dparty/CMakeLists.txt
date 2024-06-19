add_subdirectory(glad)

# set(OMNI_GLAD_INTEGRATION ON)
# include_directories("glad/include")
# add_subdirectory(omni_types)

set(GLFW_BUILD_DOCS OFF CACHE BOOL  "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL  "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)

set(ENABLE_OPT 0)
set(SHADERC_SKIP_TESTS ON)
set(SHADERC_SKIP_EXAMPLES ON)
set(SHADERC_SKIP_COPYRIGHT_CHECK ON)
add_subdirectory(glslang)

add_subdirectory("Vulkan-Headers")

add_subdirectory(stb)

add_subdirectory(imgui)
add_subdirectory(miniaudio)
