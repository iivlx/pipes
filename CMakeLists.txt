cmake_minimum_required (VERSION 3.20)

project(Pipes)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME})

add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(src)
