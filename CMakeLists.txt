cmake_minimum_required(VERSION 3.30)

project(Ort)

set(CMAKE_CXX_STANDARD 11)

find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)

file(GLOB_RECURSE SOURCES "token/*.cpp" "lexer/*.cpp" "ast/*.cpp")

add_executable(Ort main.cpp ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ./)
target_link_libraries(${PROJECT_NAME} fmt::fmt)
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)
