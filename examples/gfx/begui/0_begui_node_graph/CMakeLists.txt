file(GLOB_RECURSE BEBONE_EXAMPLE_BEGUI_0_NODE_GRAPH *.cpp)

include_directories("./")
include_directories(${BEBONE_INCLUDES})

add_executable(Bebone_Example_Begui_0_Node_Graph ${BEBONE_EXAMPLE_BEGUI_0_NODE_GRAPH})
target_link_libraries(Bebone_Example_Begui_0_Node_Graph bebone)