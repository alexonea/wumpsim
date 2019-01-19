add_subdirectory(core)
add_subdirectory(gui)

set(SOURCES
  main.cpp
)

add_executable(wumpsim ${SOURCES})
target_link_libraries(wumpsim wumpcore wumpgui)
