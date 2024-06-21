file(GLOB_RECURSE BEBONE_ASSETS_SRC_FILES "*.cpp")

include_directories(
    "${CMAKE_SOURCE_DIR}/3dparty/stb"
    "${CMAKE_SOURCE_DIR}/3dparty/glad/include"
)

add_library(bebone_assets STATIC ${BEBONE_ASSETS_SRC_FILES})

target_link_libraries(bebone_assets stb_image)
target_link_libraries(bebone_assets stb_image_write)
