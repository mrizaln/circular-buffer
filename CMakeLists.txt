cmake_minimum_required(VERSION 3.12)

project(
  circbuf
  VERSION 0.1.0
  LANGUAGES CXX
  DESCRIPTION "A simple C++ circular buffer written in C++20"
)

string(
  COMPARE EQUAL
  "${CMAKE_CURRENT_SOURCE_DIR}"
  "${CMAKE_SOURCE_DIR}"
  CIRCBUF_STANDALONE
)

option(CIRCBUF_BUILD_EXAMPLES "Build example programs" ${CIRCBUF_STANDALONE})
option(CIRCBUF_BUILD_TESTS "Build example programs" ${CIRCBUF_STANDALONE})

add_library(circbuf INTERFACE)
target_include_directories(circbuf INTERFACE include)
target_compile_features(circbuf INTERFACE cxx_std_20)
set_target_properties(circbuf PROPERTIES CXX_EXTENSIONS OFF)

if(CIRCBUF_BUILD_TESTS)
  add_subdirectory(test)
endif()

if(CIRCBUF_BUILD_EXAMPLES)
  add_subdirectory(example)
endif()
