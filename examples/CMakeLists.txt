cmake_minimum_required(VERSION 3.21)
project(BeboneExamples)

include_directories("./")
include_directories("../src")
include_directories("../3dparty/glad/include")
include_directories("../3dparty/glfw/include")
include_directories("../3dparty/Vulkan-Headers/include")
include_directories("../3dparty/omni_types/src")
include_directories("../3dparty/stb")
include_directories("../3dparty/imgui")

add_subdirectory(gfx)
add_subdirectory(assets)
add_subdirectory(core)
