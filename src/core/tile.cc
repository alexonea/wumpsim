/*
 *  tile.cc
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

#include <core/tile.h>

namespace wumpus
{
  void
  Tile::resetUp(const TilePtr& pTile)
  {
    m_pUp = pTile;
  }

  void
  Tile::resetDown(const TilePtr& pTile)
  {
    m_pDown = pTile;
  }

  void
  Tile::resetLeft(const TilePtr& pTile)
  {
    m_pLeft = pTile;
  }

  void
  Tile::resetRight(const TilePtr& pTile)
  {
    m_pRight = pTile;
  }

  void
  Tile::resetUp(Tile* pTile)
  {
    m_pUp.reset(pTile);
  }

  void
  Tile::resetDown(Tile* pTile)
  {
    m_pDown.reset(pTile);
  }

  void
  Tile::resetLeft(Tile* pTile)
  {
    m_pLeft.reset(pTile);
  }

  void
  Tile::resetRight(Tile* pTile)
  {
    m_pRight.reset(pTile);
  }

  TilePtr
  Tile::getUp() const
  {
    return m_pUp;
  }

  TilePtr
  Tile::getDown() const
  {
    return m_pDown;
  }

  TilePtr
  Tile::getLeft() const
  {
    return m_pLeft;
  }

  TilePtr
  Tile::getRight() const
  {
    return m_pRight;
  }

  TilePtr&
  Tile::getUp() noexcept
  {
    return m_pUp;
  }

  TilePtr&
  Tile::getDown() noexcept
  {
    return m_pDown;
  }

  TilePtr&
  Tile::getLeft() noexcept
  {
    return m_pLeft;
  }

  TilePtr&
  Tile::getRight() noexcept
  {
    return m_pRight;
  }

  Tile*
  Tile::getUpRaw () const
  {
    return m_pUp.get();
  }

  Tile*
  Tile::getDownRaw() const
  {
    return m_pDown.get();
  }

  Tile*
  Tile::getLeftRaw() const
  {
    return m_pLeft.get();
  }

  Tile*
  Tile::getRightRaw() const
  {
    return m_pRight.get();
  }
}
