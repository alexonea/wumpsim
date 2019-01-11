/*
 *  room.h
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

#ifndef SRC_CORE_ROOM_H
#define SRC_CORE_ROOM_H 1

#include <core/room_decl.h>

#include <core/tile.h>
#include <core/player_decl.h>

namespace wumpus
{
  enum RoomContent
  {
    EMPTY = 0,
    PIT,
    WUMPUS,
    GOLD,
  };

  class Room : public Tile
  {
  public:
    Room(const RoomContent& eContent = EMPTY) noexcept;

    void        setPlayer     (PlayerPtr&& pPlayer);
    PlayerPtr&& releasePlayer ();
  private:
    RoomContent m_eContent;
    /*
     * Each room holds a pointer to a player. This guarantees that only one
     * player can occupy a tile at all times. Moving a player from one time
     * to another is done by moving the pointer.
     */
    PlayerPtr m_pPlayer;
  };
}

#endif
