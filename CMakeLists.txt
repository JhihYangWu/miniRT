cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_NAME "miniRT")
project("${PROJECT_NAME}")

set(CMAKE_BUILD_TYPE Release)

add_subdirectory(src)
