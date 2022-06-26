target_include_directories(${PROJECT_NAME}_lib PUBLIC
 ./
 gui/
)

target_include_directories(${PROJECT_NAME}_curses PUBLIC
 pdcurses/
 gui/curses/
)

target_include_directories(${PROJECT_NAME}_opengl PUBLIC
 glew/
 SDL2/
 SDL2_ttf/
 gui/opengl/
)