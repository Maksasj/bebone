file(GLOB_RECURSE BEBONE_EXAMPLE_GFX_OPENGL_1_OPENGL_HELLO_TRIANGLE *.cpp)

include_directories("../../src")
include_directories("./")

add_executable(Bebone_Example_Gfx_1_Opengl_Hello_Triangle ${BEBONE_EXAMPLE_GFX_OPENGL_1_OPENGL_HELLO_TRIANGLE})
target_link_libraries(Bebone_Example_Gfx_1_Opengl_Hello_Triangle bebone)