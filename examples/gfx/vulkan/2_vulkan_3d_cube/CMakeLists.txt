file(GLOB_RECURSE BEBONE_EXAMPLE_GFX_VULKAN_2_VULKAN_3D_CUBE *.cpp)

include_directories("../../src")
include_directories("./")

add_executable(Bebone_Example_Gfx_2_Vulkan_3D_Cube ${BEBONE_EXAMPLE_GFX_VULKAN_2_VULKAN_3D_CUBE})
target_link_libraries(Bebone_Example_Gfx_2_Vulkan_3D_Cube bebone)