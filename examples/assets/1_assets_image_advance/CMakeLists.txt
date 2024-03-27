file(GLOB_RECURSE BEBONE_EXAMPLE_ASSETS_0_IMAGE_ADVANCE *.cpp)

include_directories("../../src")
include_directories("./")

add_executable(Bebone_Example_Assets_0_Image_Advance ${BEBONE_EXAMPLE_ASSETS_0_IMAGE_ADVANCE})
target_link_libraries(Bebone_Example_Assets_0_Image_Advance bebone)