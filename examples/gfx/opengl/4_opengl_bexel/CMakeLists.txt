file(GLOB_RECURSE BEBONE_EXAMPLE_GFX_OPENGL_4_OPENGL_BEXEL *.cpp)

include_directories("../../src")
include_directories("./")

add_executable(Bebone_Example_Gfx_4_Opengl_Bexel ${BEBONE_EXAMPLE_GFX_OPENGL_4_OPENGL_BEXEL})
target_link_libraries(Bebone_Example_Gfx_4_Opengl_Bexel bebone)
target_link_libraries(Bebone_Example_Gfx_4_Opengl_Bexel stb_perlin)