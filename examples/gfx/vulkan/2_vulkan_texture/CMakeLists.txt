file(GLOB_RECURSE BEBONE_EXAMPLE_GFX_VULKAN_2_VULKAN_TEXTURE *.cpp)

include_directories("./")
include_directories(${BEBONE_INCLUDES})

add_executable(Bebone_Example_Gfx_2_Vulkan_Texture ${BEBONE_EXAMPLE_GFX_VULKAN_2_VULKAN_TEXTURE})
target_link_libraries(Bebone_Example_Gfx_2_Vulkan_Texture bebone)