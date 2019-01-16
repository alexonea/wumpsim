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

namespace wumpus
{
  class Room
  {
  public:
    Room(const RoomContent& eContent = EMPTY) noexcept;

    void        setContent    (const RoomContent& eContent) noexcept;
    RoomContent getContent    () const noexcept;
  private:
    RoomContent m_eContent;
  };
}

#endif
