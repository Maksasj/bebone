file(GLOB_RECURSE BEBONE_CORE_SRC_FILES "*.cpp")

# Since we also building gfx module
# lets include glad headers for omni_types library
if(BEBONE_BUILD_GFX)
    add_compile_definitions(OMNI_GLAD_INTEGRATION)
    include_directories("../../../3dparty/glad/include")
endif()

include_directories("../../../3dparty/omni_types/src")

add_library(bebone_core STATIC ${BEBONE_CORE_SRC_FILES})

target_link_libraries(bebone_core omni_types)
