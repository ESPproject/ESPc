project(ESPc)
cmake_minimum_required(VERSION 3.22)
set(target_name esp)
set(ltest lexer_test)

add_library(
    ${target_name} STATIC
    Lexer/Lexer.cpp
    Lexer/Lexer.hpp
    Lexer/Location.hpp
    Lexer/Token.cpp
    Lexer/Token.hpp
)
add_executable(
    ${ltest}
    Tests/Lexer_Tests/Test1.cpp
)

target_link_libraries(
    ${ltest}
    ${target_name}
)

include(cmake/CompileOptions.cmake)
set_compile_options(${target_name})

target_include_directories(
    ${target_name}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_include_directories(
    ${ltest}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)