# Adding bebone modules as subdirectories
if(BEBONE_BUILD_CORE)
    add_subdirectory(core)
endif()

if(BEBONE_BUILD_ASSETS)
    add_subdirectory(assets)
endif()

if(BEBONE_BUILD_GFX)
    add_subdirectory(gfx)
endif()

if(BEBONE_BUILD_RENDERER)
    add_subdirectory(renderer)
endif()

# Source files
file(GLOB BEBONE_SRC_FILE bebone.cpp)
add_library(bebone STATIC ${BEBONE_SRC_FILE})

# Linking all bebone modules
if(BEBONE_BUILD_GFX)
    target_link_libraries(bebone bebone_gfx)
endif()

if(BEBONE_BUILD_ASSETS)
    target_link_libraries(bebone bebone_assets)
endif()

if(BEBONE_BUILD_CORE)
    target_link_libraries(bebone bebone_core)
endif()

if(BEBONE_BUILD_RENDERER)
    target_link_libraries(bebone bebone_renderer)
endif()

set(BEBONE_INCLUDES "${CMAKE_SOURCE_DIR}/src")

list(APPEND BEBONE_INCLUDES ${BEBONE_ASSETS_INCLUDES})   
list(APPEND BEBONE_INCLUDES ${BEBONE_CORE_INCLUDES})   
list(APPEND BEBONE_INCLUDES ${BEBONE_GFX_INCLUDES})   
list(APPEND BEBONE_INCLUDES ${BEBONE_RENDERER_INCLUDES})   

# Set BEBONE_INCLUDES as global variable 
set(BEBONE_INCLUDES "${BEBONE_INCLUDES}" CACHE INTERNAL "")
