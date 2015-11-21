cmake_minimum_required (VERSION 2.8.8)
project (Assignment5)

# include directories
include_directories( include )

# add sources
file(GLOB SOURCES "src/*.cpp")
add_executable(main ${SOURCES})

# add test
add_subdirectory(lib/gtest-1.7.0)
add_subdirectory(test)

# add the install targets
install ( TARGETS main DESTINATION "${PROJECT_SOURCE_DIR}/bin" )
