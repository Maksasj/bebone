file(GLOB_RECURSE BEBONE_ASSETS_SRC_FILES "*.cpp")

include_directories("../../../3dparty/stb")
# include_directories("../../../3dparty/omni_types/src")

add_library(bebone_assets STATIC ${BEBONE_ASSETS_SRC_FILES})

target_link_libraries(bebone_assets stb_image)
target_link_libraries(bebone_assets stb_image_write)
