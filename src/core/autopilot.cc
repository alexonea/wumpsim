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

#include <gui/logger.h>

namespace wumpus
{
  AutoPilot::AutoPilot()
  : Agent{}
  {
    m_pCurrent->getGuess().markSafe();
    m_map.insert(std::make_pair(m_pCurrent->getRelativePos(), m_pCurrent));
  }

  Action
  AutoPilot::doNext(const Percept& sensors, PlayerOrientation eOrientation)
  {
    if (m_pCurrent->getGuess().isSafe())
    {
      markSafe(m_pCurrent);
    }
    else
    {
      if (!sensors.isActive(BREEZE))
        markSafe(m_pCurrent, PC_PIT);

      if (!sensors.isActive(STENCH))
        markSafe(m_pCurrent, PC_WUMPUS);
    }


    if (m_cb)
      m_cb(m_pCurrent, eOrientation);
    
    m_pCurrent = std::static_pointer_cast<Path> (m_pCurrent->getRight());

    return FORWARD;
  }

  void
  AutoPilot::linkNeighbours(PathPtr pCenter)
  {
    Position pos = pCenter->getRelativePos();
    
    {
      auto it = m_map.find(getRelative(pos, LEFT));
      if (it != m_map.end())
      {
        Logger::getInstance().log("linked (%d, %d) with (%d, %d)\n",
          pos.first, pos.second,
          getRelative(pos, LEFT).first, getRelative(pos, LEFT).second);
        pCenter->resetLeft(it->second);
        it->second->resetRight(pCenter);
      }
    }

    {
      auto it = m_map.find(getRelative(pos, UP));
      if (it != m_map.end())
      {
        Logger::getInstance().log("linked (%d, %d) with (%d, %d)\n",
          pos.first, pos.second,
          getRelative(pos, UP).first, getRelative(pos, UP).second);
        pCenter->resetUp(it->second);
        it->second->resetDown(pCenter);
      }
    }

    {
      auto it = m_map.find(getRelative(pos, DOWN));
      if (it != m_map.end())
      {
        Logger::getInstance().log("linked (%d, %d) with (%d, %d)\n",
          pos.first, pos.second,
          getRelative(pos, DOWN).first, getRelative(pos, DOWN).second);
        pCenter->resetDown(it->second);
        it->second->resetUp(pCenter);
      }
    }

    {
      auto it = m_map.find(getRelative(pos, RIGHT));
      if (it != m_map.end())
      {
        Logger::getInstance().log("linked (%d, %d) with (%d, %d)\n",
          pos.first, pos.second,
          getRelative(pos, RIGHT).first, getRelative(pos, RIGHT).second);
        pCenter->resetRight(it->second);
        it->second->resetLeft(pCenter);
      }
    }
  }

  void
  AutoPilot::markSafe(const PathPtr& pCurrent, const PathContent& eContent)
  {
    Position pos = pCurrent->getRelativePos();

    PathPtr pLeft   = std::static_pointer_cast<Path> (pCurrent->getLeft());
    PathPtr pRight  = std::static_pointer_cast<Path> (pCurrent->getRight());
    PathPtr pUp     = std::static_pointer_cast<Path> (pCurrent->getUp());
    PathPtr pDown   = std::static_pointer_cast<Path> (pCurrent->getDown());
    
    if (!pLeft)
    {
      pLeft = PathPtr{new Path{getRelative(pos, LEFT)}};
      m_map.insert(std::make_pair(getRelative(pos, LEFT), pLeft));
    }

    if (!pRight)
    {
      pRight = PathPtr{new Path{getRelative(pos, RIGHT)}};
      m_map.insert(std::make_pair(getRelative(pos, RIGHT), pRight));
    }

    if (!pUp)
    {
      pUp = PathPtr{new Path{getRelative(pos, UP)}};
      m_map.insert(std::make_pair(getRelative(pos, UP), pUp));
    }

    if (!pDown)
    {
      pDown = PathPtr{new Path{getRelative(pos, DOWN)}};
      m_map.insert(std::make_pair(getRelative(pos, DOWN), pDown));
    }

    linkNeighbours(pLeft);
    linkNeighbours(pRight);
    linkNeighbours(pUp);
    linkNeighbours(pDown);

    Logger::getInstance().log("created left = %p\n", pCurrent->getLeftRaw());
    Logger::getInstance().log("created right = %p\n", pCurrent->getRightRaw());
    Logger::getInstance().log("created down = %p\n", pCurrent->getDownRaw());
    Logger::getInstance().log("created up = %p\n", pCurrent->getUpRaw());

    if (eContent == OK)
    {
      Logger::getInstance().log("marked as OK\n");
      pLeft->getGuess().markSafe();
      pRight->getGuess().markSafe();
      pUp->getGuess().markSafe();
      pDown->getGuess().markSafe();
    }
    else
    {
      pLeft->getGuess().clear(eContent);
      pRight->getGuess().clear(eContent);
      pUp->getGuess().clear(eContent);
      pDown->getGuess().clear(eContent);
    }
  }
}
