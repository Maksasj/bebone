file(GLOB_RECURSE BEBONE_IMGUI_SRC_FILES "*.cpp")

include_directories("../../../3dparty/imgui")
include_directories("../../../3dparty/glfw/include")

file(GLOB BEBONE_IMGUI_SRC
    "../../../3dparty/imgui/*.cpp"
    "../../../3dparty/imgui/backends/imgui_impl_glfw.cpp"
    "../../../3dparty/imgui/backends/imgui_impl_opengl3.cpp"
)

list (APPEND BEBONE_IMGUI_SRC_FILES ${BEBONE_IMGUI_SRC})

add_library(bebone_imgui STATIC ${BEBONE_IMGUI_SRC_FILES})