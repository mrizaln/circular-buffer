cmake_minimum_required(VERSION 3.16)
project(circbuf-test VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_COLOR_DIAGNOSTICS ON) # You might want to enable this (CMake 3.24+)

find_package(ut REQUIRED)
find_package(fmt REQUIRED)

add_subdirectory(lib/circbuf) # emits circbuf target

add_executable(circular_buffer_test circular_buffer_test.cpp)
target_link_libraries(circular_buffer_test PRIVATE Boost::ut fmt::fmt circbuf)
target_compile_options(circular_buffer_test PRIVATE -Wall -Wextra -Wconversion)

# sanitizer
# ~~~
target_compile_options(circular_buffer_test PRIVATE -fsanitize=address,leak,undefined)
target_link_options(circular_buffer_test PRIVATE -fsanitize=address,leak,undefined)

# run the test
# ~~~
enable_testing()
add_test(NAME circular_buffer_test COMMAND $<TARGET_FILE:circular_buffer_test>)

add_custom_command(
  TARGET circular_buffer_test
  POST_BUILD
  COMMAND circular_buffer_test)
