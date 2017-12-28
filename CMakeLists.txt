cmake_minimum_required (VERSION 3.1)

project (lansort)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-O3 -Werror -Wall -Wextra")

add_executable (lansort main.cpp estimate.cpp measure.cpp)
