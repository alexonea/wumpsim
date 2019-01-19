/*
 *  world.cc
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

#include <core/world.h>

namespace wumpus
{
  World::World(unsigned nRows, unsigned nCols)
  : m_nRows{nRows}
  , m_nCols{nCols}
  , m_vRooms{nRows * nCols}
  {}

  void
  World::setRoomType(const RoomContent& eContent, unsigned iX, unsigned iY)
  {
    if (iX >= m_nRows || iY >= m_nCols)
      return;

    unsigned long p = iX * m_nRows + iY;
    m_vRooms[p].setContent(eContent);
  }

  RoomContent
  World::getRoomType(unsigned iX, unsigned iY)
  {
    if (iX >= m_nRows || iY >= m_nCols)
      return INVALID;

    unsigned long p = iX * m_nRows + iY;
    return m_vRooms[p].getContent();
  }
}
