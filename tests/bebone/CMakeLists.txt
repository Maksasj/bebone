cmake_minimum_required(VERSION 3.21)
project(BeboneTests)

include_directories("../../src")
include_directories("../../3dparty/glad/include")
include_directories("../../3dparty/glfw/include")
include_directories("../../3dparty/Vulkan-Headers/include")
include_directories("../../3dparty/stb")
include_directories("../../3dparty/imgui")

add_subdirectory(core)

# Register bebone all tests target
file(GLOB_RECURSE SRC_FILES "*.cpp")
add_executable(bebone_all_tests ${SRC_FILES})
target_link_libraries(bebone_all_tests bebone_core)
target_link_libraries(bebone_all_tests gtest gtest_main)