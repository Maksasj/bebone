file(GLOB_RECURSE BEBONE_EXAMPLE_INPUT_0_KEYBOARD *.cpp)

include_directories("../../src")
include_directories("./")

add_executable(Bebone_Example_Input_0_Keyboard ${BEBONE_EXAMPLE_INPUT_0_KEYBOARD})
target_link_libraries(Bebone_Example_Input_0_Keyboard bebone)