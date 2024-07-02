file(GLOB_RECURSE BEBONE_EXAMPLE_RENDERER_0_WINDOW *.cpp)

include_directories(".")
include_directories(${BEBONE_INCLUDES})

add_executable(Bebone_Example_Renderer_0_Renderer_Window ${BEBONE_EXAMPLE_RENDERER_0_WINDOW})
target_link_libraries(Bebone_Example_Renderer_0_Renderer_Window bebone)