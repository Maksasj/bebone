file(GLOB_RECURSE SRC_FILES "*.cpp")

if(OMNI_GLAD_INTEGRATION)
    add_compile_definitions(OMNI_GLAD_INTEGRATION)
endif ()

add_library(omni_types STATIC ${SRC_FILES})
