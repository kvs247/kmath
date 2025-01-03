include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(ops_test
  test/Ops/testOps.cpp
)
target_link_libraries(ops_test
  PRIVATE
  kmath
  gtest
  gtest_main
)

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

add_executable(eigen_test
  test/Matrix/testEigen.cpp
)
target_link_libraries(eigen_test
  PRIVATE
  kmath
  gtest
  gtest_main
)

add_executable(gram_schmidt_qr_test
  test/Matrix/QR/testGramSchmidtQR.cpp
)
target_link_libraries(gram_schmidt_qr_test
  PRIVATE
  kmath
  gtest
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(ops_test)
gtest_discover_tests(matrix_test)
gtest_discover_tests(vector_test)
gtest_discover_tests(eigen_test)
gtest_discover_tests(gram_schmidt_qr_test)
