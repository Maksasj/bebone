file(GLOB_RECURSE BEBONE_EXAMPLE_GFX_VULKAN_0_VULKAN_WINDOW *.cpp)

include_directories("../../src")
include_directories("./")

add_executable(Bebone_Example_Gfx_0_Vulkan_Window ${BEBONE_EXAMPLE_GFX_VULKAN_0_VULKAN_WINDOW})
target_link_libraries(Bebone_Example_Gfx_0_Vulkan_Window bebone)