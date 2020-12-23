cmake_minimum_required(VERSION 3.2)

project(allocator)

add_executable(allocator src/main.cpp)
set_target_properties(allocator PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

if (MSVC)
    target_compile_options(allocator PRIVATE
        /W4
    )
else ()
    target_compile_options(allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()
