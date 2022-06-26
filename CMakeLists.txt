cmake_minimum_required (VERSION 3.20)

project(Pipes)

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/x86)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/x86)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/x64)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/x64)
endif()


add_library(${PROJECT_NAME}_lib STATIC)

add_executable(${PROJECT_NAME}_curses)
target_link_libraries(${PROJECT_NAME}_curses ${PROJECT_NAME}_lib)

add_executable(${PROJECT_NAME}_opengl)
target_link_libraries(${PROJECT_NAME}_opengl ${PROJECT_NAME}_lib)

add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(src)
