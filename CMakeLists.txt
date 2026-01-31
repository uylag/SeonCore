cmake_minimum_required(VERSION 3.16)
project(seoncore LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(seoncore src/main.cpp)
target_include_directories(seoncore PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(seoncore_tests tests/main_test.cpp)
target_include_directories(seoncore_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (MSVC)
    target_compile_options(seoncore PRIVATE /W4)
    target_compile_options(seoncore_tests PRIVATE /W4)
else()
    target_compile_options(seoncore PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(seoncore_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()
add_test(NAME seoncore_tests COMMAND seoncore_tests)


