cmake_minimum_required(VERSION 3.21)
project(OmniTypesExamples)

include_directories("../src")

add_executable(omni_types_example_1 example_1.cpp)
target_link_libraries(omni_types_example_1 omni_types)

add_executable(omni_types_example_2 example_2.cpp)
target_link_libraries(omni_types_example_2 omni_types)

add_executable(omni_types_example_3 example_3.cpp)
target_link_libraries(omni_types_example_3 omni_types)

add_executable(omni_types_example_4 example_4.cpp)
target_link_libraries(omni_types_example_4 omni_types)

add_executable(omni_types_example_5 example_5.cpp)
target_link_libraries(omni_types_example_5 omni_types)