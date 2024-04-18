file(GLOB_RECURSE BEBONE_EXAMPLE_EVENTS_0_EVENT_LISTENERS *.cpp)

include_directories("../../src")
include_directories(".")

add_executable(Bebone_Example_Events_0_Event_Listeners ${BEBONE_EXAMPLE_EVENTS_0_EVENT_LISTENERS})
target_link_libraries(Bebone_Example_Events_0_Event_Listeners bebone)