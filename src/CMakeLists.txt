cmake_minimum_required(VERSION 3.12.0)

add_executable(ip_filter main.cpp)
add_library(ip_lib IP.cpp)
add_library(utils_lib Utils.cpp)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra;"
)

target_link_libraries(ip_filter ip_lib utils_lib stdc++fs)

