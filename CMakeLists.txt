cmake_minimum_required (VERSION 3.20)

project(Pipes)

set(SOURCE_FILES
 src/gui/gui_curses.cpp
 src/gui/gui_curses_commands.cpp
 src/gui/PipeWindow.cpp
 src/directions.cpp
 src/PipeGrid.cpp
 src/PipeCell.cpp
 src/PipeGridSolver.cpp
 src/generator.cpp
 src/random.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
 include/
 include/gui/
 include/pdcurses/
)

target_link_directories(${PROJECT_NAME} PUBLIC
 include/
 include/gui/
 include/pdcurses/
 lib/pdcurses
)

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
  target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/pdcurses/x86/pdcurses.lib)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
  target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/pdcurses/x64/pdcurses.lib)
endif()