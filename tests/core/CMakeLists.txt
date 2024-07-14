include_directories("./")

file(GLOB_RECURSE SRC_FILES "*.cpp")
set(EXECUTABLES)

foreach(SRC_FILE ${SRC_FILES})
    get_filename_component(TEST_NAME ${SRC_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${SRC_FILE})
    target_link_libraries(${TEST_NAME} bebone_core)
    target_link_libraries(${TEST_NAME} gtest gtest_main)
    list(APPEND EXECUTABLES ${TEST_NAME})
endforeach()

add_custom_target(run_all_tests COMMAND ${CMAKE_COMMAND} -E echo "Running all unit tests...")

foreach(EXECUTABLE ${EXECUTABLES})
    add_custom_command(TARGET run_all_tests POST_BUILD
            COMMAND ${EXECUTABLE}
            COMMENT "Running test ${EXECUTABLE}"
    )
endforeach()