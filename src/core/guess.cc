/*
 *  guess.cc
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

#include <core/guess.h>

namespace wumpus
{
  Guess::Guess() noexcept
  : m_bWumpus{true}
  , m_bPit{true}
  {}

  void
  Guess::markSafe() noexcept
  {
    m_bPit = false;
    m_bWumpus = false;
  }

  void
  Guess::clear(const PathContent& eContent) noexcept
  {
    switch (eContent)
    {
      case WUMPUS:
      {
        m_bWumpus = false;
        break;
      }
      case PIT:
      {
        m_bPit = false;
        break;
      }
      default:
        return;
    }
  }

  bool
  Guess::isSafe() const noexcept
  {
    return (m_bWumpus == false && m_bPit == false);
  }
}
