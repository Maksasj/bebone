set(BEBONE_SOUND_INCLUDES
    "${CMAKE_SOURCE_DIR}/src/bebone/sound"
    "${CMAKE_SOURCE_DIR}/3dparty/miniaudio"
    "${CMAKE_SOURCE_DIR}/3dparty/stb" # Todo fix this cringe
    "${CMAKE_SOURCE_DIR}/3dparty/glad/include" # Todo fix this cringe
    "${CMAKE_SOURCE_DIR}/3dparty/glfw/include" # Todo fix this cringe
    "${CMAKE_SOURCE_DIR}/3dparty/Vulkan-Headers/include" # Todo fix this cringe
)

set(BEBONE_SOUND_INCLUDES "${BEBONE_SOUND_INCLUDES}" CACHE INTERNAL "")
include_directories(${BEBONE_SOUND_INCLUDES})

file(GLOB_RECURSE BEBONE_SOUND_SRC_FILES "*.cpp")
add_library(bebone_sound STATIC ${BEBONE_SOUND_SRC_FILES})

target_link_libraries(bebone_sound miniaudio)
target_link_libraries(bebone_sound bebone_core)
