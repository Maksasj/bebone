file(GLOB_RECURSE BEBONE_EXAMPLE_RENDERER_3_MESH *.cpp)

include_directories(".")
include_directories(${BEBONE_INCLUDES})

add_executable(Bebone_Example_Renderer_3_Renderer_Mesh ${BEBONE_EXAMPLE_RENDERER_3_MESH})
target_link_libraries(Bebone_Example_Renderer_3_Renderer_Mesh bebone)