set ( GCC_COVERAGE_COMPILE_FLAGS "-Wall -std=c++11" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_library(Oset oset.hpp)
set_target_properties(Oset PROPERTIES LINKER_LANGUAGE CXX)
