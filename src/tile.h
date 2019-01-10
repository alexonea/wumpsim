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

#include <memory>

#include "player.h"

namespace wumpus
{
  enum TileContent
  {
    EMPTY = 0,
    PIT,
    WUMPUS,
    GOLD,
  };

  class Tile;
  using TilePtr = std::shared_ptr<Tile>;

  class Tile
  {
  public:
    Tile(TileContent eContent = EMPTY) noexcept;

    void resetUp    (const TilePtr& pTile);
    void resetDown  (const TilePtr& pTile);
    void resetLeft  (const TilePtr& pTile);
    void resetRight (const TilePtr& pTile);
  private:
    TileContent m_eContent;

    /*
     * Each tile holds 4 pointers to the neighbouring tiles. This allows for
     * two "realistic" effects: 1) each player (if more than one) can act
     * independently and in parallel (with proper synchronization) and 2) the
     * tiles can be configured in non-grid patterns and allow loops, shortcuts
     * and more. Shared pointers are used because one tile is referenced by
     * more than one neighbouring tile.
     */
    TilePtr                 m_pUp;
    TilePtr                 m_pDown;
    TilePtr                 m_pLeft;
    TilePtr                 m_pRight;

    /*
     * Each tile also holds a pointer to a player. This guarantees that only
     * one player can occupy a tile at all times. Moving a player from one time
     * to another is done by moving the pointer.
     */
    std::unique_ptr<Player> m_pPlayer;
  };
}

#endif
