/*
 *  tile.h
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

#ifndef SRC_TILE_H
#define SRC_TILE_H 1

#include <cstdint>

namespace wumpus
{
  enum Sensor
  {
    BREEZE = 0,
    STENCH,
    GLTTER,
    ROAR,
    BUMP,
  };

  enum TileContent
  {
    EMPTY = 0,
    PLAYER,
    PIT,
    WUMPUS,
    GOLD,
  };

  using TileSensors = std::uint8_t;

  class Tile
  {
  public:
    Tile(TileContent eContent = EMPTY);
    
    void setSensor    (Sensor sensor) noexcept;
    void clearSensor  (Sensor sensor) noexcept;
    bool getSensor    (Sensor sensor) const noexcept;
  private:
    TileSensors m_sensors;
    TileContent m_eContent;
  };
}

#endif
