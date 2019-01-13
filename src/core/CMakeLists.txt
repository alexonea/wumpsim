set(SOURCES
  tile.cc
  room.cc
  world.cc
  sensor.cc
  player.cc
  error.cc
  agent.cc
  autopilot.cc
  path.cc
  guess.cc
)

add_library(wumpcore ${SOURCES})
