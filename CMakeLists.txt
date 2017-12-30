cmake_minimum_required(VERSION 3.9)
project(C_Merge_Sort C)

set(CMAKE_C_STANDARD 11)

add_executable(C_Merge_Sort main.c)

target_link_libraries(C_Merge_Sort m)