add_subdirectory(gtest-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include)

set(TEST_SOURCES main_test.cpp)
add_executable(sample_tests ${TEST_SOURCES})

target_link_libraries(sample_tests gtest_main)
