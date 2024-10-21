file(GLOB_RECURSE BEBONE_EXAMPLE_RENDERER_2_SPRITE *.cpp)

include_directories(".")
include_directories(${BEBONE_INCLUDES})

add_executable(Bebone_Example_Renderer_2_Renderer_Sprite ${BEBONE_EXAMPLE_RENDERER_2_SPRITE})
target_link_libraries(Bebone_Example_Renderer_2_Renderer_Sprite bebone)