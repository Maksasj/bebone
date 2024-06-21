set(BEBONE_CORE_INCLUDES
    "${CMAKE_SOURCE_DIR}/src/bebone/core"
    "${CMAKE_SOURCE_DIR}/3dparty/glad/include"
)

set(BEBONE_CORE_INCLUDES "${BEBONE_CORE_INCLUDES}" CACHE INTERNAL "")
include_directories(${BEBONE_CORE_INCLUDES})

file(GLOB_RECURSE BEBONE_CORE_SRC_FILES "*.cpp")
add_library(bebone_core STATIC ${BEBONE_CORE_SRC_FILES})
