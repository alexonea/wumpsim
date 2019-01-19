/*
 *  player_decl.h
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

#ifndef SRC_CORE_PLAYER_DECL_H
#define SRC_CORE_PLAYER_DECL_H 1

#include <memory>
#include <functional>
#include <ostream>
#include <string>

#include <core/sensor.h>
#include <core/tile_decl.h>
#include <core/position.h>


namespace wumpus
{
  enum Orientation
  {
    UP = 0,
    LEFT,
    DOWN,
    RIGHT,
  };

  extern std::string   toString  (Orientation o);
  extern std::ostream& operator<<(std::ostream& os, Orientation o);

  using Percept = SensorData;
  using TilePos = std::pair<Position, TileRef>;
  using PrintCb = std::function<void(const TileRef&, Orientation, Percept)>;

  class Player;
}

#endif
