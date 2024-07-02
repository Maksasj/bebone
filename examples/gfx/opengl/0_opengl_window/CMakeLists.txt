file(GLOB_RECURSE BEBONE_EXAMPLE_GFX_OPENGL_0_OPENGL_WINDOW *.cpp)

include_directories("./")
include_directories(${BEBONE_INCLUDES})

add_executable(Bebone_Example_Gfx_0_Opengl_Window ${BEBONE_EXAMPLE_GFX_OPENGL_0_OPENGL_WINDOW})
target_link_libraries(Bebone_Example_Gfx_0_Opengl_Window bebone)