target_sources(${PROJECT_NAME} PUBLIC
 directions.cpp
 PipeGrid.cpp
 PipeCell.cpp
 PipeGridSolver.cpp
 generator.cpp
 random.cpp
)

add_subdirectory(gui)
