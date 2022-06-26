# curses

target_link_directories(${PROJECT_NAME}_curses PUBLIC
 lib/pdcurses
)

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
  target_link_libraries(${PROJECT_NAME}_curses ${PROJECT_SOURCE_DIR}/lib/pdcurses/x86/pdcurses.lib)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
  target_link_libraries(${PROJECT_NAME}_curses ${PROJECT_SOURCE_DIR}/lib/pdcurses/x64/pdcurses.lib)
endif()

# opengl

find_package(OpenGL REQUIRED)
find_package(GLU REQUIRED)
target_link_libraries(${PROJECT_NAME}_opengl ${OPENGL_LIBRARIES} ${GLU_LIBRARY} )

target_link_directories(${PROJECT_NAME}_opengl PUBLIC
 lib/glew
 lib/SDL2
 lib/SDL2_ttf
)

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
  target_link_libraries(${PROJECT_NAME}_opengl ${PROJECT_SOURCE_DIR}/lib/glew/x86/glew32.lib)
  target_link_libraries(${PROJECT_NAME}_opengl ${PROJECT_SOURCE_DIR}/lib/glew/x86/glew32s.lib)
  target_link_libraries(${PROJECT_NAME}_opengl ${PROJECT_SOURCE_DIR}/lib/SDL2/x86/SDL2.lib)
  target_link_libraries(${PROJECT_NAME}_opengl ${PROJECT_SOURCE_DIR}/lib/SDL2/x86/SDL2main.lib)
  target_link_libraries(${PROJECT_NAME}_opengl ${PROJECT_SOURCE_DIR}/lib/SDL2/x86/SDL2test.lib)
  target_link_libraries(${PROJECT_NAME}_opengl ${PROJECT_SOURCE_DIR}/lib/SDL2_ttf/x86/SDL2_ttf.lib)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
  target_link_libraries(${PROJECT_NAME}_opengl ${PROJECT_SOURCE_DIR}/lib/glew/x64/glew32.lib)
  target_link_libraries(${PROJECT_NAME}_opengl ${PROJECT_SOURCE_DIR}/lib/glew/x64/glew32s.lib)
  target_link_libraries(${PROJECT_NAME}_opengl ${PROJECT_SOURCE_DIR}/lib/SDL2/x64/SDL2.lib)
  target_link_libraries(${PROJECT_NAME}_opengl ${PROJECT_SOURCE_DIR}/lib/SDL2/x64/SDL2main.lib)
  target_link_libraries(${PROJECT_NAME}_opengl ${PROJECT_SOURCE_DIR}/lib/SDL2/x64/SDL2test.lib)
  target_link_libraries(${PROJECT_NAME}_opengl ${PROJECT_SOURCE_DIR}/lib/SDL2_ttf/x64/SDL2_ttf.lib)
endif()
