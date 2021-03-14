cmake_minimum_required(VERSION 3.12.0)

add_executable(ip_filter main.cpp)
add_library(ip_lib IP.cpp)
add_library(utils_lib Utils.cpp)

target_link_libraries(ip_filter ip_lib utils_lib)