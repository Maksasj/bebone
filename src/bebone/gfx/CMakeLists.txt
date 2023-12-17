file(GLOB_RECURSE BEBONE_GFX_SRC_FILES "*.cpp")

#Including dependency headers
include_directories("../../../3dparty/glad/include")
include_directories("../../../3dparty/glfw/include")
include_directories("../../../3dparty/Vulkan-Headers/include")
include_directories("../../../3dparty/omni_types/src")
include_directories("../../../3dparty/stb")
include_directories("../../../3dparty/glfw/include")

include_directories("./")

#Including imgui headers
include_directories("../../../3dparty/imgui")

#Adding imgui source files
file(GLOB BEBONE_IMGUI_SRC
        "../../../3dparty/imgui/*.cpp"
        "../../../3dparty/imgui/backends/imgui_impl_glfw.cpp"
        "../../../3dparty/imgui/backends/imgui_impl_opengl3.cpp"
)
list (APPEND BEBONE_GFX_SRC_FILES ${BEBONE_IMGUI_SRC})

#Finally making an bebone_gfx library
add_library(bebone_gfx STATIC ${BEBONE_GFX_SRC_FILES})

find_package(Vulkan REQUIRED)

target_link_libraries(bebone_gfx glfw)
target_link_libraries(bebone_gfx stb_image)
target_link_libraries(bebone_gfx glad)
target_link_libraries(bebone_gfx glslang)
target_link_libraries(bebone_gfx SPIRV)
target_link_libraries(bebone_gfx glslang-default-resource-limits)
target_link_libraries(bebone_gfx ${Vulkan_LIBRARIES})

