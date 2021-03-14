cmake_minimum_required(VERSION 3.10.0)

add_executable(unit_test main.cpp)

target_include_directories(unit_test PUBLIC ../src)
add_test(unit-tests unit_test)
target_link_libraries(unit_test ip_lib utils_lib gtest)