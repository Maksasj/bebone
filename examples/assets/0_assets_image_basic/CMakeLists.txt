file(GLOB_RECURSE BEBONE_EXAMPLE_ASSETS_0_IMAGE_BASIC *.cpp)

include_directories("./")
include_directories(${BEBONE_INCLUDES})

add_executable(Bebone_Example_Assets_0_Image_Basic ${BEBONE_EXAMPLE_ASSETS_0_IMAGE_BASIC})
target_link_libraries(Bebone_Example_Assets_0_Image_Basic bebone)