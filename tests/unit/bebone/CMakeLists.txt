cmake_minimum_required(VERSION 3.21)
project(BeboneTests)

include_directories("../../../src")
include_directories("../../../3dparty/glad/include")
include_directories("../../../3dparty/glfw/include")
include_directories("../../../3dparty/Vulkan-Headers/include")
include_directories("../../../3dparty/omni_types/src")
include_directories("../../../3dparty/stb")
include_directories("../../../3dparty/imgui")

add_subdirectory(core)
