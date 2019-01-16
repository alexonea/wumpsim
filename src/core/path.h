/*
 *  path.h
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

#ifndef SRC_CORE_PATH_H
#define SRC_CORE_PATH_H 1

#include <core/path_decl.h>
#include <core/player_decl.h>

#include <utility>

#include <core/sensor.h>
#include <core/tile.h>

namespace wumpus
{
  class Path : public Tile
  {
  public:
    Path(const Position& pos);

    Guess&    getGuess() noexcept;
    Position  getRelativePos() const noexcept;
  private:
    Guess     m_eGuess;
    Position  m_relativePos;
  };

  Position getRelative(const Position& current, PlayerOrientation eOrientation);
}

#endif
