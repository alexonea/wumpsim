/*
 *  path.cc
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

#include <core/path.h>

namespace wumpus
{
  Path::Path(const Position& pos)
  : m_relativePos{pos}
  {}

  Guess&
  Path::getGuess() noexcept
  {
    return m_eGuess;
  }

  Position
  Path::getRelativePos() const noexcept
  {
    return m_relativePos;
  }

  Position
  getRelative(const Position& current, PlayerOrientation eOrientation)
  {
    Position p = current;
    switch (eOrientation)
    {
      case UP:
      {
        p.second++;
        break;   
      }
      case DOWN:
      {
        p.second--;
        break;
      }
      case LEFT:
      {
        p.first--;
        break;
      }
      case RIGHT:
      {
        p.first++;
        break;
      }
    }

    return p;
  }
}
