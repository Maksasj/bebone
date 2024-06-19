file(GLOB_RECURSE BEBONE_EXAMPLE_GFX_OPENGL_6_OPENGL_IMGUI *.cpp)

include_directories("./")
include_directories(${BEBONE_INCLUDES})

add_executable(Bebone_Example_Gfx_6_Opengl_Imgui ${BEBONE_EXAMPLE_GFX_OPENGL_6_OPENGL_IMGUI})
target_link_libraries(Bebone_Example_Gfx_6_Opengl_Imgui bebone)