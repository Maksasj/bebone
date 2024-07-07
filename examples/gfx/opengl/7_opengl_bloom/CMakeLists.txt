file(GLOB_RECURSE BEBONE_EXAMPLE_GFX_OPENGL_7_OPENGL_BLOOM *.cpp)

include_directories("./")
include_directories(${BEBONE_INCLUDES})

add_executable(Bebone_Example_Gfx_7_Opengl_Bloom ${BEBONE_EXAMPLE_GFX_OPENGL_7_OPENGL_BLOOM})
target_link_libraries(Bebone_Example_Gfx_7_Opengl_Bloom bebone)