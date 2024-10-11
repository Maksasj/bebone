file(GLOB_RECURSE BEBONE_EXAMPLE_RENDERER_3_SCENE *.cpp)

include_directories(".")
include_directories(${BEBONE_INCLUDES})

add_executable(Bebone_Example_Renderer_4_Renderer_Scene ${BEBONE_EXAMPLE_RENDERER_3_SCENE})
target_link_libraries(Bebone_Example_Renderer_4_Renderer_Scene bebone)