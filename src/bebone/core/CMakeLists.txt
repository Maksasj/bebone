set(BEBONE_CORE_INCLUDES "${CMAKE_SOURCE_DIR}/src/bebone/core" )

# Since we also building gfx module
# lets include glad headers for omni_types library
if(BEBONE_BUILD_GFX)
    add_compile_definitions(OMNI_GLAD_INTEGRATION)
    list(APPEND BEBONE_CORE_INCLUDES "${CMAKE_SOURCE_DIR}/3dparty/glad/include") 
endif()

# list(APPEND BEBONE_CORE_INCLUDES "${CMAKE_SOURCE_DIR}/3dparty/omni_types/src") 

set(BEBONE_CORE_INCLUDES "${BEBONE_CORE_INCLUDES}" CACHE INTERNAL "")
include_directories(${BEBONE_CORE_INCLUDES})

file(GLOB_RECURSE BEBONE_CORE_SRC_FILES "*.cpp")
add_library(bebone_core STATIC ${BEBONE_CORE_SRC_FILES})
# target_link_libraries(bebone_core omni_types)
