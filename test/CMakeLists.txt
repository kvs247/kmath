include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(matrix_test
  test/Matrix/testMatrix.cpp
)
target_link_libraries(matrix_test
  PRIVATE
  kmath
  gtest
  gtest_main
)

add_executable(vector_test
  test/Matrix/testVector.cpp
)
target_link_libraries(vector_test
  PRIVATE
  kmath
  gtest
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(matrix_test)
gtest_discover_tests(vector_test)
