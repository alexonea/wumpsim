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

#include <sstream>

namespace wumpus
{
  Guess::Guess() noexcept
  : m_bWumpus{true}
  , m_bPit{true}
  , m_bPermanent{false}
  {}

  void
  Guess::markSafe() noexcept
  {
    m_bPit = false;
    m_bWumpus = false;
    m_bPermanent = true;
  }

  void
  Guess::clear(const PathContent& eContent) noexcept
  {
    if (m_bPermanent)
      return;

    switch (eContent)
    {
      case PC_WUMPUS:
      {
        m_bWumpus = false;
        break;
      }
      case PC_PIT:
      {
        m_bPit = false;
        break;
      }
      default:
        return;
    }

    if (isSafe())
      m_bPermanent = true;
  }

  bool
  Guess::isSafe() const noexcept
  {
    return (m_bWumpus == false && m_bPit == false);
  }

  void
  Guess::markPermanent() noexcept
  {
    m_bPermanent = true;
  }

  bool
  Guess::isPermanent() const noexcept
  {
    return m_bPermanent;
  }

  std::string
  Guess::toString() const
  {
    std::stringstream ss;
    
    if (isPermanent())
    {
      if (isSafe())
        ss << "OK";
      else if (m_bPit)
        ss << "PIT";
      else
        ss << "WUMPUS";
    }
    else
    {
      if (m_bPit)
        ss << "P? ";

      if (m_bWumpus)
        ss << "W?";
    }

    return ss.str();
  }
}
