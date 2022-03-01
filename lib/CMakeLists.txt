target_link_directories(${PROJECT_NAME} PUBLIC
 lib/pdcurses
)

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
  target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/pdcurses/x86/pdcurses.lib)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
  target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/pdcurses/x64/pdcurses.lib)
endif()
