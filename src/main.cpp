/*
 *  main.cpp
 *
 *  Copyright (C) 2019 Alexandru N. Onea <alexandru.onea@toporcomputing.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <core/player.h>
#include <core/world.h>
#include <core/autopilot.h>
#include <gui/graphics.h>
#include <gui/box.h>
#include <gui/logger.h>
#include <gui/print.h>

#include <iostream>

int
main(int argc, char const *argv[])
{
  using namespace wumpus;

  auto & g = Graphics::getInstance();

  World w{4, 4};

  {
    PlayerPtr pPlayer{new Player{}};
    AgentPtr  pAgent{new AutoPilot{}};

    pAgent->afterUpdate(print);

    pPlayer->setAgent(std::move(pAgent));
    w.setPlayer(std::move(pPlayer));
  }

  w.setRoomType(WUMPUS, 2, 0);
  w.setRoomType(PIT, 2, 2);
  w.setRoomType(PIT, 3, 3);
  w.setRoomType(PIT, 0, 2);
  w.setRoomType(GOLD, 3, 2);

  // unsigned key;
  // do
  // {
  //   Logger::getInstance().log("This is an error");
  // } while ((key = g.waitNextKey()) != 'q');
  
  try
  {
    do
    {
      unsigned key = g.waitNextKey();
      if (key == 'q' || key == 'Q')
        break;

    } while (w.update());
  }
  catch (...)
  {

  }


  return 0;
}
