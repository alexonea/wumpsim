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
  Tile::Tile(TileContent eContent) noexcept
  : m_eContent{eContent}
  {}

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
  Tile::setPlayer(PlayerPtr&& pPlayer)
  {
    m_pPlayer = std::move(pPlayer);
  }

  PlayerPtr&&
  Tile::releasePlayer()
  {
    return std::move(m_pPlayer);
  }
}
