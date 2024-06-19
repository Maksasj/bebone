file(GLOB_RECURSE BEBONE_GFX_SRC_FILES "*.cpp")

include_directories("../../../3dparty/glad/include")
include_directories("../../../3dparty/glfw/include")
include_directories("../../../3dparty/Vulkan-Headers/include")

# add_compile_definitions(OMNI_GLAD_INTEGRATION)
# include_directories("../../../3dparty/omni_types/src")

include_directories("../../../3dparty/stb")
include_directories("../../../3dparty/glfw/include")
include_directories("../../../3dparty/imgui")

include_directories("./")

add_library(bebone_gfx STATIC ${BEBONE_GFX_SRC_FILES})

find_package(Vulkan REQUIRED)

target_link_libraries(bebone_gfx glfw)
target_link_libraries(bebone_gfx stb_image)
target_link_libraries(bebone_gfx glad)
target_link_libraries(bebone_gfx glslang)
target_link_libraries(bebone_gfx SPIRV)
target_link_libraries(bebone_gfx glslang-default-resource-limits)
target_link_libraries(bebone_gfx ${Vulkan_LIBRARIES})
target_link_libraries(bebone_gfx imgui)
