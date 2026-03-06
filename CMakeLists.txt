cmake_minimum_required(VERSION 3.16)

project(the_archaeologist VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# main executable
add_executable(the_archaeologist
    src/main.cpp
)

target_include_directories(the_archaeologist
    PRIVATE include
)

# warnings
if (MSVC)
    target_compile_options(the_archaeologist PRIVATE /W4)
else()
    target_compile_options(the_archaeologist PRIVATE -Wall -Wextra -Wpedantic)
endif()

# tests
enable_testing()

add_executable(archaeologist_tests
    tests/test_main.cpp
    tests/basic_test.cpp
    tests/build_test.cpp
)

add_test(NAME archaeologist_tests COMMAND archaeologist_tests)