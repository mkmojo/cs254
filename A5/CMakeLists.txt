cmake_minimum_required (VERSION 3.3)
project ( Assignment5 C CXX )

# include headers
include_directories( include )

# add implementations
add_subdirectory(src)

# add test
add_subdirectory(test)
