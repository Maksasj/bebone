file(GLOB_RECURSE BEBONE_EXAMPLE_SOUND_1_STREAMING_SOUND *.cpp)

include_directories("./")
include_directories(${BEBONE_INCLUDES})

add_executable(Bebone_Example_Sound_1_Streaming_Sound ${BEBONE_EXAMPLE_SOUND_1_STREAMING_SOUND})
target_link_libraries(Bebone_Example_Sound_1_Streaming_Sound bebone)