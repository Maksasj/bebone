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