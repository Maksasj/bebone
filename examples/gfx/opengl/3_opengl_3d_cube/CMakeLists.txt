file(GLOB_RECURSE BEBONE_EXAMPLE_GFX_OPENGL_3_OPENGL_3D_CUBE *.cpp)

include_directories("../../src")
include_directories("./")

add_executable(Bebone_Example_Gfx_3_Opengl_3D_Cube ${BEBONE_EXAMPLE_GFX_OPENGL_3_OPENGL_3D_CUBE})
target_link_libraries(Bebone_Example_Gfx_3_Opengl_3D_Cube bebone)