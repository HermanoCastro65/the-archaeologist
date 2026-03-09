cmake_minimum_required(VERSION 3.16)

project(the_archaeologist VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ----------------------------
# include directories
# ----------------------------
include_directories(${PROJECT_SOURCE_DIR}/include)

# ----------------------------
# core source files
# ----------------------------
set(ARCHAEOLOGIST_SOURCES
    src/scanner/directory_scanner.cpp
    src/runner/self_runner.cpp
    src/report/project_report.cpp
    src/config/ignore_config.cpp
)

# ----------------------------
# pybind11
# ----------------------------
include(FetchContent)

FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v2.12.0
)

FetchContent_MakeAvailable(pybind11)

# ----------------------------
# main executable
# ----------------------------
add_executable(the_archaeologist
    src/main.cpp
    ${ARCHAEOLOGIST_SOURCES}
)

target_include_directories(the_archaeologist
    PRIVATE ${PROJECT_SOURCE_DIR}/include
)

# ----------------------------
# python bindings
# ----------------------------
pybind11_add_module(archaeologist_py
    bindings/python_module.cpp
    ${ARCHAEOLOGIST_SOURCES}
)

target_include_directories(archaeologist_py
    PRIVATE ${PROJECT_SOURCE_DIR}/include
)

set_target_properties(archaeologist_py
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/python
)

# ----------------------------
# tests
# ----------------------------
enable_testing()

add_executable(archaeologist_tests
    tests/test_main.cpp
    tests/_build/basic_test.cpp
    tests/_build/build_test.cpp
    tests/scanner/directory_scanner_test.cpp
    tests/scanner/directory_scanner_list_test.cpp
    tests/scanner/directory_scanner_ignore_test.cpp
    tests/runner/self_runner_test.cpp
    tests/scanner/directory_tree_list_test.cpp
    tests/report/project_report_test.cpp
    tests/scanner/scanner_ignore_config_test.cpp
    ${ARCHAEOLOGIST_SOURCES}
)

target_include_directories(archaeologist_tests
    PRIVATE ${PROJECT_SOURCE_DIR}/include
)

add_test(NAME archaeologist_tests COMMAND archaeologist_tests)

# ----------------------------
# warnings
# ----------------------------
if (MSVC)

    target_compile_options(the_archaeologist PRIVATE /W4)
    target_compile_options(archaeologist_py PRIVATE /W4)
    target_compile_options(archaeologist_tests PRIVATE /W4)

else()

    target_compile_options(the_archaeologist PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(archaeologist_py PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(archaeologist_tests PRIVATE -Wall -Wextra -Wpedantic)

endif()