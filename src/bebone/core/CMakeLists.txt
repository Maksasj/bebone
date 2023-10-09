file(GLOB_RECURSE BEBONE_CORE_SRC_FILES "*.cpp")

include_directories("../../../3dparty/omni_types/src")

add_library(bebone_core STATIC ${BEBONE_CORE_SRC_FILES})