file(GLOB_RECURSE BEBONE_EXAMPLE_SOUND_0_PLAYING_SOUND *.cpp)

include_directories("./")
include_directories(${BEBONE_INCLUDES})

add_executable(Bebone_Example_Sound_0_Playing_Sound ${BEBONE_EXAMPLE_SOUND_0_PLAYING_SOUND})
target_link_libraries(Bebone_Example_Sound_0_Playing_Sound bebone)