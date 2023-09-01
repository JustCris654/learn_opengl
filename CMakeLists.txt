cmake_minimum_required(VERSION 3.19)

project(
  opengl_conan
  DESCRIPTION "Project to learn opengl"
  LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_TOOLCHAIN_FILE conan_toolchain.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -g -O0")
set(glad_DIR build/)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(libs/shader)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
    "."
)

find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE libs/shader)

target_link_libraries(${PROJECT_NAME} shader)

target_link_libraries(${PROJECT_NAME} glfw glad::glad)
