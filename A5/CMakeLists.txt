cmake_minimum_required (VERSION 3.3)
project ( Assignment5 C CXX )

# include directories
include_directories( include )

# add implementation
add_subdirectory(src)

# add test
add_subdirectory(test)
