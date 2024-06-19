add_executable(omni_types_matrix_multiplication matrix_multiplication.cpp)
target_link_libraries(omni_types_matrix_multiplication omni_types)

enable_testing()

add_test(NAME Omnitypes_Matrix_Multiplication COMMAND $<TARGET_FILE:omni_types_matrix_multiplication>)