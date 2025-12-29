include(cmake/fetched-libs.cmake)

function(make_test NAME)
  add_executable(${NAME} source/${NAME}.cpp)
  target_link_libraries(${NAME} PRIVATE circbuf Boost::ut)
  target_compile_features(${NAME} PRIVATE cxx_std_20)
  set_target_properties(${NAME} PROPERTIES CXX_EXTENSIONS OFF)

  if(NOT MSVC)
    target_compile_options(${NAME} PRIVATE -Wall -Wextra -Wconversion)
    target_compile_options(${NAME} PRIVATE -fsanitize=address,leak,undefined)
    target_link_options(${NAME} PRIVATE -fsanitize=address,leak,undefined)
  else()
    target_compile_options(${NAME} PRIVATE /W4)
  endif()

  add_test(NAME ${NAME} COMMAND $<TARGET_FILE:${NAME}>)
  add_custom_command(TARGET ${NAME} POST_BUILD COMMAND ${NAME})
endfunction()

enable_testing()

make_test(raw_buffer_test)
make_test(circbuf_test)
