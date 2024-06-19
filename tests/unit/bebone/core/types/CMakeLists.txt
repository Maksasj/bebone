cmake_minimum_required(VERSION 3.21)
project(OmniTypesTests)

include_directories("../src")
include_directories("./")

enable_testing()

add_subdirectory(matrix)
