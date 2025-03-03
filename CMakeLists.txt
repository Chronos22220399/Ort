cmake_minimum_required(VERSION 3.30)

project(Ort)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCES "token/*.cpp" "lexer/*.cpp")

add_executable(Ort main.cpp
        ${SOURCES}
        lexer/lexer.cpp
        lexer/lexer.h)

target_include_directories(${PROJECT_NAME} PRIVATE ./)
