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

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt)
endif()
