/*
 *  position.cc
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

#include <core/position.h>

namespace wumpus
{
  Position::Position(const std::pair<int, int>& pos)
  : m_pos{pos}
  {}

  Position::Position(int iX, int iY)
  : Position{{iX, iY}}
  {}

  bool
  operator<(const Position& first, const Position& second)
  {
    return (first.m_pos < second.m_pos);
  }

  bool
  operator==(const Position& first, const Position& second)
  {
    return (first.m_pos == second.m_pos);
  }

  Position
  up(const Position& current)
  {
    return Position(current.m_pos.first + 1, current.m_pos.second);
  }
  
  Position
  down(const Position& current)
  {
    return Position(current.m_pos.first - 1, current.m_pos.second);
  }
  
  Position
  left(const Position& current)
  {
    return Position(current.m_pos.first, current.m_pos.second - 1);
  }
  
  Position
  right(const Position& current)
  {
    return Position(current.m_pos.first, current.m_pos.second + 1);
  }
}
