add_subdirectory(gtest-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include)

file(GLOB TEST_SOURCES ${PROJECT_SOURCE_DIR}/test/*.cpp)
add_executable(oset_test ${TEST_SOURCES})
install(TARGETS oset_test DESTINATION ${PROJECT_SOURCE_DIR}/bin)

target_link_libraries(oset_test gtest_main)

add_test(oset_test oset_test)
