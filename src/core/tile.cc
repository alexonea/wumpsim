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
  Tile::Tile(Position relPosition)
  : m_relPosition{relPosition}
  , m_nVisited{0}
  {}

  TileRef
  Tile::resetUp(const TileRef& pTile)
  {
    return (m_pUp = pTile);
  }

  TileRef
  Tile::resetDown(const TileRef& pTile)
  {
    return (m_pDown = pTile);
  }

  TileRef
  Tile::resetLeft(const TileRef& pTile)
  {
    return (m_pLeft = pTile);
  }

  TileRef
  Tile::resetRight(const TileRef& pTile)
  {
    return (m_pRight = pTile);
  }

  TileRef
  Tile::getUp() const
  {
    return m_pUp;
  }

  TileRef
  Tile::getDown() const
  {
    return m_pDown;
  }

  TileRef
  Tile::getLeft() const
  {
    return m_pLeft;
  }

  TileRef
  Tile::getRight() const
  {
    return m_pRight;
  }

  void
  Tile::setPosition(const Position& relPosition)
  {
    m_relPosition = relPosition;
  }

  Position
  Tile::getPosition() const
  {
    return m_relPosition;
  }

  void
  Tile::setVisited(bool bVisited) noexcept
  {
    if (bVisited)
      m_nVisited++;
    else
      m_nVisited--;
  }

  bool
  Tile::isVisited() const noexcept
  {
    return (m_nVisited > 0);
  }

  int
  Tile::score() const noexcept
  {
    return GuessData::score() + 10 * isVisited() - 4 * m_nVisited;
  }
}
