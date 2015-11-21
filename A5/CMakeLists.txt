cmake_minimum_required (VERSION 2.8.8)
project (Assignment5)

# include directories
include_directories( include )

# use library
# include_directories ( "${PROJECT_SOURCE_DIR}/lib" )
# add_subdirectory (lib)

# add sources
file(GLOB SOURCES "src/*.cpp")

add_executable(main ${SOURCES})

# add the executable
# target_link_libraries (main Oset) 

# add the install targets
install ( TARGETS main DESTINATION "${PROJECT_SOURCE_DIR}/bin" )
