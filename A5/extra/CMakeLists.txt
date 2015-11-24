cmake_minimum_required(VERSION 3.3)
project(Assignment5 C CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_FLAGS} -std=c++11")
find_package(Threads REQUIRED)

# include headers
include_directories(include)

# add implementations
add_subdirectory(src)

# add test
 add_subdirectory(test)
