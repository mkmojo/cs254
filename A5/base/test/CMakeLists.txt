add_subdirectory(gtest-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include)

file(GLOB TEST_SOURCES ${PROJECT_SOURCE_DIR}/test/*.cpp)
add_executable(sample_tests ${TEST_SOURCES})
install(TARGETS sample_tests DESTINATION ${PROJECT_SOURCE_DIR}/test)

target_link_libraries(sample_tests gtest_main)

add_test(sample_tests sample_tests)
