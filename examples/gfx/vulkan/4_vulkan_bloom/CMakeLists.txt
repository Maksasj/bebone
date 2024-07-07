file(GLOB_RECURSE BEBONE_EXAMPLE_GFX_VULKAN_4_VULKAN_BLOOM *.cpp)

include_directories("./")
include_directories(${BEBONE_INCLUDES})

add_executable(Bebone_Example_Gfx_4_Vulkan_Bloom ${BEBONE_EXAMPLE_GFX_VULKAN_4_VULKAN_BLOOM})
target_link_libraries(Bebone_Example_Gfx_4_Vulkan_Bloom bebone)