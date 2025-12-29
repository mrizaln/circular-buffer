if(MSVC)
  set(COMPILE_FLAGS /W4)
else()
  set(COMPILE_FLAGS -Wall -Wextra -Wconversion)
endif()

add_executable(simple source/simple.cpp)
target_link_libraries(simple PRIVATE circbuf)
target_compile_options(simple PRIVATE ${COMPILE_FLAGS})

# # sanitizer
# target_compile_options(simple PRIVATE -fsanitize=address,leak,undefined)
# target_link_options(simple PRIVATE -fsanitize=address,leak,undefined)

find_package(Boost)

if(Boost_FOUND)
  message(STATUS "circbuf: Boost found, building bench.cpp")

  add_executable(bench source/bench.cpp)
  target_link_libraries(bench PRIVATE circbuf Boost::boost)
  target_compile_options(bench PRIVATE ${COMPILE_FLAGS})

  # # sanitizer
  # target_compile_options(simple PRIVATE -fsanitize=address,leak,undefined)
  # target_link_options(simple PRIVATE -fsanitize=address,leak,undefined)
else()
  message(STATUS "circbuf: Can't find Boost, not building bench.cpp")
endif()
