file(GLOB_RECURSE BEBONE_EXAMPLE_GFX_OPENGL_5_OPENGL_FLAPPY_BIRD *.cpp)

include_directories("../../src")
include_directories("./")

add_executable(Bebone_Example_Gfx_5_Opengl_Flappy_Bird ${BEBONE_EXAMPLE_GFX_OPENGL_5_OPENGL_FLAPPY_BIRD})
target_link_libraries(Bebone_Example_Gfx_5_Opengl_Flappy_Bird bebone)
