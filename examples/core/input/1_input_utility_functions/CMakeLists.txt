file(GLOB_RECURSE BEBONE_EXAMPLE_INPUT_1_UTILITY_FUNCTIONS *.cpp)

include_directories("./")
include_directories(${BEBONE_INCLUDES})

add_executable(Bebone_Example_Input_1_Utility_Functions ${BEBONE_EXAMPLE_INPUT_1_UTILITY_FUNCTIONS})
target_link_libraries(Bebone_Example_Input_1_Utility_Functions bebone)