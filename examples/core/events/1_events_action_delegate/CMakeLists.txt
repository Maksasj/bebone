file(GLOB_RECURSE BEBONE_EXAMPLE_EVENTS_1_ACTION_DELEGATE *.cpp)

include_directories("./")
include_directories(${BEBONE_INCLUDES})

add_executable(Bebone_Example_Events_1_Action_Delegate ${BEBONE_EXAMPLE_EVENTS_1_ACTION_DELEGATE})
target_link_libraries(Bebone_Example_Events_1_Action_Delegate bebone)