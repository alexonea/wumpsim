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

#ifndef SRC_CORE_TILE_H
#define SRC_CORE_TILE_H 1
 
#include <core/tile_decl.h>

#include <core/guess.h>

namespace wumpus
{
  class Tile : public GuessData
  {
  public:
    Tile(Position relPosition = {0, 0});

    TileRef   resetUp      (const TileRef& pTile);
    TileRef   resetDown    (const TileRef& pTile);
    TileRef   resetLeft    (const TileRef& pTile);
    TileRef   resetRight   (const TileRef& pTile);

    TileRef   getUp    () const;
    TileRef   getDown  () const;
    TileRef   getLeft  () const;
    TileRef   getRight () const;

    void      setPosition(const Position& relPosition);
    Position  getPosition() const;

    void      setVisited(bool bVisited = true) noexcept;
    bool      isVisited() const noexcept;
    
    virtual int score() const noexcept override;
  private:
    /*
     * Each tile holds 4 pointers to the neighbouring tiles.
     */
    TileRef   m_pUp;
    TileRef   m_pDown;
    TileRef   m_pLeft;
    TileRef   m_pRight;

    Position  m_relPosition;

    int       m_nVisited;
  };
}

#endif
