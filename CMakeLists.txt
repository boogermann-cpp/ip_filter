cmake_minimum_required(VERSION 3.10.0)

project(ip_filter VERSION 0.0.1)

# set(CMAKE_VERBOSE_MAKEFILE ON)

enable_testing()

add_subdirectory(src)
add_subdirectory(lib/gtest)
add_subdirectory(test)





find_program (BASH_PROGRAM bash)
find_program(UNIT_TEST unit_test)

if (BASH_PROGRAM)
  add_test (functional-test ${BASH_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/test/test.sh)
endif (BASH_PROGRAM)

set(CPACK_GENERATOR DEB)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "podlog2@gmail.com")

include(CPack)
include(CTest)

