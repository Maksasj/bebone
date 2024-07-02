file(GLOB_RECURSE BEBONE_EXAMPLE_ASSETS_1_IMAGE_ADVANCE *.cpp)

include_directories("./")
include_directories(${BEBONE_INCLUDES})

add_executable(Bebone_Example_Assets_1_Image_Advance ${BEBONE_EXAMPLE_ASSETS_1_IMAGE_ADVANCE})
target_link_libraries(Bebone_Example_Assets_1_Image_Advance bebone)