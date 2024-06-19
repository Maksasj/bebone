file(GLOB_RECURSE BEBONE_EXAMPLE_GFX_OPENGL_2_OPENGL_TEXTURE *.cpp)

include_directories("./")
include_directories(${BEBONE_INCLUDES})

add_executable(Bebone_Example_Gfx_2_Opengl_Texture ${BEBONE_EXAMPLE_GFX_OPENGL_2_OPENGL_TEXTURE})
target_link_libraries(Bebone_Example_Gfx_2_Opengl_Texture bebone)