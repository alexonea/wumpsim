set(SOURCES
  graphics.cc
  window.cc
  print.cc
  logger.cc
  box.cc
)

add_library(wumpgui ${SOURCES})
target_link_libraries(wumpgui wumpcore ncurses)
