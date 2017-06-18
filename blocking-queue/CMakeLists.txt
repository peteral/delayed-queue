# cmake -H. -Bbuild
# cmake --build build
# cd build && make
cmake_minimum_required (VERSION 2.8)

project (blocking-queue-test)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories("${PROJECT_SOURCE_DIR}")

add_executable(blocking-queue-test ${PROJECT_SOURCE_DIR}/blocking-queue-test.cpp)
target_link_libraries(blocking-queue-test pthread boost_unit_test_framework)

