cmake_minimum_required(VERSION 3.16)
project(example VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost)

add_subdirectory(lib/circbuf)

function(create_exe name)
    add_executable(${name} source/${name}.cpp)
    target_include_directories(${name} PRIVATE source)
    target_link_libraries(${name} PRIVATE circbuf boost::boost)
    target_compile_options(${name} PRIVATE -Wall -Wextra -Wconversion -Wswitch-enum)

    # sanitizer
    target_compile_options(${name} PRIVATE -fsanitize=address,leak,undefined)
    target_link_options(${name} PRIVATE -fsanitize=address,leak,undefined)
endfunction()

create_exe(simple)
create_exe(bench)
