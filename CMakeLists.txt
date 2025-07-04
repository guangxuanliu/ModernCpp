cmake_minimum_required (VERSION 3.20)

project ("ModernCpp")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)


add_subdirectory ("C++11")
add_subdirectory ("C++14")
add_subdirectory ("C++17")
add_subdirectory ("C++20 Part1")

add_subdirectory ("Test")

