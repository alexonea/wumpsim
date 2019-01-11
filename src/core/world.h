/*
 *  world.h
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

#ifndef SRC_CORE_WORLD_H
#define SRC_CORE_WORLD_H 1

#include <vector>

#include <core/room_decl.h>
#include <core/player_decl.h>

namespace wumpus
{
  using PosIndex = long long;

  class World
  {
  public:
    World(unsigned nRows, unsigned nCols);

    void setPlayer(PlayerPtr&& pPlayer, unsigned iX = 1, unsigned iY = 1);
  private:
    unsigned             m_nRows;
    unsigned             m_nCols;
    std::vector<RoomPtr> m_vpTiles;

    PosIndex nextUp     (PosIndex current) const noexcept;
    PosIndex nextDown   (PosIndex current) const noexcept;
    PosIndex nextLeft   (PosIndex current) const noexcept;
    PosIndex nextRight  (PosIndex current) const noexcept;
    PosIndex toPosIndex (unsigned iX, unsigned iY) const noexcept;
    bool     isValid    (unsigned iX, unsigned iY) const noexcept;
    bool     isValid    (PosIndex current) const noexcept;
  };
}

#endif
