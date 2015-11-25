add_subdirectory(gtest-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include)

file(GLOB TEST_SOURCES ${PROJECT_SOURCE_DIR}/test/*.cpp)
add_executable(oset_tests ${TEST_SOURCES})
install(TARGETS oset_tests DESTINATION ${PROJECT_SOURCE_DIR}/bin)

target_link_libraries(oset_tests gtest_main)

add_test(oset_tests oset_tests)
