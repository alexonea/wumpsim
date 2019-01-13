/*
 *  autopilot.cc
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

#include <core/autopilot.h>

#include <core/path.h>
#include <core/error.h>

namespace wumpus
{
  AutoPilot::AutoPilot()
  : m_pCurrent{new Path{}}
  {
    m_pCurrent->getGuess().markSafe();
  }

  Action
  AutoPilot::doNext(const Percept& sensors)
  {
    if (m_pCurrent->getGuess().isSafe())
    {
      markSafe(m_pCurrent);
    }
    else
    {
      if (!sensors.isActive(BREEZE))
        markSafe(m_pCurrent, PIT);

      if (!sensors.isActive(STENCH))
        markSafe(m_pCurrent, WUMPUS);
    }

    return CLIMB;
  }

  void
  AutoPilot::markSafe(const PathPtr& pCurrent, const PathContent& eContent)
  {
    PathPtr pLeft   = std::static_pointer_cast<Path>(pCurrent->getLeft());
    PathPtr pRight  = std::static_pointer_cast<Path>(pCurrent->getRight());
    PathPtr pUp     = std::static_pointer_cast<Path>(pCurrent->getUp());
    PathPtr pDown   = std::static_pointer_cast<Path>(pCurrent->getDown());

    if (eContent == OK)
    {
      if (pLeft)
        pLeft->getGuess().markSafe();

      if (pRight)
        pRight->getGuess().markSafe();

      if (pUp)
        pUp->getGuess().markSafe();

      if (pDown)
        pDown->getGuess().markSafe();
    }
    else
    {
      if (pLeft)
        pLeft->getGuess().clear(eContent);

      if (pRight)
        pRight->getGuess().clear(eContent);

      if (pUp)
        pUp->getGuess().clear(eContent);

      if (pDown)
        pDown->getGuess().clear(eContent);
    }
  }
}
