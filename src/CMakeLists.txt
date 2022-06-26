target_sources(${PROJECT_NAME}_lib PUBLIC
 directions.cpp
 PipeGrid.cpp
 PipeCell.cpp
 PipeGridSolver.cpp
 generator.cpp
 random.cpp
)

add_subdirectory(gui)
