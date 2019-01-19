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
#include <core/game.h>

#include <gui/graphics.h>
#include <gui/print.h>

#include <iostream>

int
main(int argc, char const *argv[])
{
  using namespace wumpus;

  auto & g = Graphics::getInstance();

  Game game{WorldRef{new World{4, 4}}};
  game.getWorld()->setRoomType(WUMPUS, 2, 0);
  game.getWorld()->setRoomType(PIT, 2, 2);
  game.getWorld()->setRoomType(PIT, 3, 3);
  game.getWorld()->setRoomType(PIT, 0, 2);
  game.getWorld()->setRoomType(GOLD, 2, 1);

  game.setPlayer(PlayerRef{new Player{}}, {0, 0});
  game.getPlayer()->setPrintCb(print);

  do
  {
      unsigned key = g.waitNextKey();
      if (key == 'q' || key == 'Q')
        break;
  } while (game.advance());


  g.waitNextKey();
  return 0;
}
