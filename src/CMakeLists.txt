add_subdirectory(core)

set(SOURCES
  main.cpp
)

add_executable(wumpsim ${SOURCES})
target_link_libraries(wumpsim wumpcore)
