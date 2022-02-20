cmake_minimum_required (VERSION 3.20)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:LIBCMT")

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

target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/pdcurses/pdcurses.lib)