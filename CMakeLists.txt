cmake_minimum_required(VERSION 3.28)
project(kmath)

add_library(kmath
  src/Matrix/Matrix.cpp
)

target_include_directories(kmath
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(matrix_test
  test/Matrix/test.cpp
)

target_link_libraries(matrix_test
  PRIVATE
    kmath
    gtest
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(matrix_test)