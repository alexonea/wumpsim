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

#include <core/error.h>
#include <core/room.h>
#include <core/player.h>

namespace wumpus
{
  World::World(unsigned nRows, unsigned nCols)
  : m_nRows{nRows}
  , m_nCols{nCols}
  {
    unsigned long nTiles = nRows * nCols;
    m_vpTiles.resize(nTiles);

    PosIndex p = 0;
    while (p < nTiles)
      /*
       * [10.01.2019] valgrind reports leaks of memory which is allocated here
       */
      m_vpTiles[p++].reset(new Room{});

    for (p = 0; p < nTiles; ++p)
    {
      PosIndex up     = nextUp(p);
      PosIndex down   = nextDown(p);
      PosIndex left   = nextLeft(p);
      PosIndex right  = nextRight(p);

      auto & pTile = m_vpTiles[p];

      if (isValid(up))
        pTile->resetUp(m_vpTiles[up]);

      if (isValid(down))
        pTile->resetDown(m_vpTiles[down]);

      if (isValid(left))
        pTile->resetDown(m_vpTiles[left]);

      if (isValid(right))
        pTile->resetDown(m_vpTiles[right]);
    }
  }

  PosIndex
  World::nextUp(PosIndex current) const noexcept
  {
    current -= m_nCols;
    return isValid(current) ? current : -1;
  }

  PosIndex
  World::nextDown(PosIndex current) const noexcept
  {
    current += m_nCols;
    return isValid(current) ? current : -1;
  }

  PosIndex
  World::nextLeft(PosIndex current) const noexcept
  {
    return (current % m_nCols == 0 ||
      !isValid(current - 1)) ? -1 : (current - 1);
  }

  PosIndex
  World::nextRight(PosIndex current) const noexcept
  {
    current++;
    return (current % m_nCols == 0 ||
      !isValid(current)) ? -1 : current;
  }

  PosIndex
  World::toPosIndex(unsigned iX, unsigned iY) const noexcept
  {
    PosIndex pos = iX * m_nCols + iY;
    return (pos >= 0 && pos < (m_nCols * m_nRows)) ? pos : -1;
  }

  bool
  World::isValid(unsigned iX, unsigned iY) const noexcept
  {
    return (iX < m_nRows && iY < m_nCols);
  }

  bool
  World::isValid(PosIndex current) const noexcept
  {
    return (current >= 0 && current < (m_nCols * m_nRows));
  }

  void
  World::setPlayer(PlayerPtr&& pPlayer, unsigned iX, unsigned iY)
  {
    if (!isValid(iX, iY))
      throw Error();

    m_vpTiles[toPosIndex(iX, iY)]->setPlayer(std::move(pPlayer));
  }
}
