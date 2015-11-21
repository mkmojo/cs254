cmake_minimum_required (VERSION 3.3)
project ( Assignment5 C CXX )

# include directories
include_directories( include )


# add test
add_subdirectory(src)
add_subdirectory(test)

# add the install targets
install ( TARGETS main DESTINATION "${PROJECT_SOURCE_DIR}/bin" )
