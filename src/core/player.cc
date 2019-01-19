/*
 *  player.cc
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

#include <core/player.h>

#include <functional>
#include <core/tile.h>
#include <algorithm>
#include <sstream>

#include <gui/logger.h>

namespace wumpus
{
  std::string
  toString(Orientation o)
  {
    std::stringstream ss;
    switch (o)
    {
      case UP: ss << "UP"; break;
      case DOWN: ss << "DOWN"; break;
      case LEFT: ss << "LEFT"; break;
      case RIGHT: ss << "RIGHT"; break;
      default: ss << "INVALID";
    }

    return ss.str();
  }

  std::ostream&
  operator<<(std::ostream& os, Orientation o)
  {
    return os << toString(o);
  }

  // bool
  // operator==(const Choice& a, const Choice& b)
  // {
  //   return (a.first == b.first);
  // }

  // bool
  // operator>(const Choice& a, const Choice& b)
  // {
  //   return (a.first > b.first);
  // }

  struct ChoiceComparator
  {
    ChoiceComparator(Orientation o) : m_eOrientation{o} {};

    bool operator() (const Choice& a, const Choice& b)
    {
      int iDiffA = 4 - (4 + a.second - m_eOrientation) % 4;
      int iDiffB = 4 - (4 + b.second - m_eOrientation) % 4;

      int iScoreA = a.first->score() + iDiffA;
      int iScoreB = b.first->score() + iDiffB;

      Logger::getInstance().log("---> %s score %d\n",
        toString(a.second).c_str(), iScoreA);
            Logger::getInstance().log("---> %s score %d\n",
        toString(b.second).c_str(), iScoreB);
      
      return (iScoreA > iScoreB);
    }
  private:
    Orientation m_eOrientation;
  };

  Player::Player(Orientation eOrientation, unsigned nArrows) noexcept
  : m_eOrientation{eOrientation}
  , m_nArrows{nArrows}
  , m_pCurrent{new Tile}
  , m_pLast{m_pCurrent}
  , m_bWumpusKilled{false}
  , m_bGoldGrabbed{false}
  {
    m_vpTiles.insert(TilePos({0, 0}, m_pCurrent));
  }

  Player::Player(unsigned nArrows) noexcept
  : Player{RIGHT, nArrows}
  {}

  void
  Player::updateSensors(const Percept& sensors) noexcept
  {
    m_sensors = sensors;
  }

  Orientation
  Player::getOrientation() const noexcept
  {
    return m_eOrientation;
  }

  void
  Player::setOrientation(const Orientation& eOrientation) noexcept
  {
    m_eOrientation = eOrientation;
  }

  unsigned
  Player::getArrows() const noexcept
  {
    return m_nArrows;
  }

  void
  Player::setArrows(unsigned nArrows) noexcept
  {
    m_nArrows = nArrows;
  }

  Action
  Player::doNextAction()
  {
    if (m_sensors.isActive(BUMP))
    {
      m_pCurrent->markBump();
      m_pCurrent = m_pLast;
      {
        std::queue<Action> q;
        m_actions.swap(q);
      }

      if (!m_vPathHome.empty())
        m_vPathHome.erase(m_vPathHome.begin() + m_vPathHome.size() - 1);
    }

    m_pCurrent->markSafe();
    m_pCurrent->setVisited();
    
    expandAround(m_pCurrent);

    if (!m_sensors.isActive(BREEZE))
      markSafeAround(m_pCurrent, GUESS_PIT);
    
    if (!m_sensors.isActive(STENCH))
      markSafeAround(m_pCurrent, GUESS_WUMPUS);

    if (m_sensors.isActive(ROAR))
      m_bWumpusKilled = true;

    if (m_printCb)
      m_printCb(m_pCurrent, m_eOrientation, m_sensors);
    
    if (!m_actions.empty())
    {
      Action next = m_actions.front();
      m_actions.pop();
      return doNext(next);
    }

    if (m_sensors.isActive(GLITTER))
    {
      m_bGoldGrabbed = true;
      return doNext(GRAB);
    }

    if (m_bWumpusKilled && m_bGoldGrabbed)
      return goHome();

    TileRef pUp     = m_pCurrent->getUp();
    TileRef pDown   = m_pCurrent->getDown();
    TileRef pLeft   = m_pCurrent->getLeft();
    TileRef pRight  = m_pCurrent->getRight();

    if (m_nArrows > 0 && !m_bWumpusKilled)
    {
      std::vector<Choice> vWumpus;
      
      if (pUp && pUp->mayBeWumpus())
        vWumpus.push_back(std::make_pair(pUp, UP));

      if (pDown && pDown->mayBeWumpus())
        vWumpus.push_back(std::make_pair(pDown, DOWN));

      if (pLeft && pLeft->mayBeWumpus())
        vWumpus.push_back(std::make_pair(pLeft, LEFT));

      if (pRight && pRight->mayBeWumpus())
        vWumpus.push_back(std::make_pair(pRight, RIGHT));

      checkWumpusLocation(vWumpus);
      if (vWumpus.size() == 1)
      {
        Choice wumpusLocation = vWumpus[0];
        return killWumpus(wumpusLocation.second);
      }
    }

    std::vector<Choice> vChoices;

    if (pUp && pUp->isSafe())
      vChoices.push_back(std::make_pair(pUp, UP));

    if (pDown && pDown->isSafe())
      vChoices.push_back(std::make_pair(pDown, DOWN));

    if (pLeft && pLeft->isSafe())
      vChoices.push_back(std::make_pair(pLeft, LEFT));

    if (pRight && pRight->isSafe())
      vChoices.push_back(std::make_pair(pRight, RIGHT));

    std::sort(vChoices.begin(), vChoices.end(),
      ChoiceComparator{m_eOrientation});

    for (auto& choice : vChoices)
      Logger::getInstance().log("    choice: %s, score=%d\n", 
        toString(choice.second).c_str(), choice.first->score());

    if (vChoices.size() == 0)
      return goHome();

    addToPathHome(vChoices[0].first);
    return turn(vChoices[0].second);
  }

  void
  Player::markSafeAround(const TileRef& pCurrent, const Guess& eGuess)
  {
    TileRef pUp     = pCurrent->getUp();
    TileRef pDown   = pCurrent->getDown();
    TileRef pLeft   = pCurrent->getLeft();
    TileRef pRight  = pCurrent->getRight();

    if (eGuess == OK)
    {
      if (pUp)
        pUp->markSafe();
      
      if (pDown)
        pDown->markSafe();
      
      if (pLeft)
        pLeft->markSafe();
      
      if (pRight)
        pRight->markSafe();
    }
    else
    {
      if (pUp)
        pUp->clear(eGuess);
      
      if (pDown)
        pDown->clear(eGuess);
      
      if (pLeft)
        pLeft->clear(eGuess);
      
      if (pRight)
        pRight->clear(eGuess);
    }
  }

  void
  Player::expandAround(const TileRef& pCurrent)
  {
    Position pos = m_pCurrent->getPosition();

    TileRef pUp     = pCurrent->getUp();
    TileRef pDown   = pCurrent->getDown();
    TileRef pLeft   = pCurrent->getLeft();
    TileRef pRight  = pCurrent->getRight();

    if (!pUp)
    {
      pUp = pCurrent->resetUp(TileRef{new Tile{up(pos)}});
      m_vpTiles.insert(std::make_pair(up(pos), pUp));
    }

    if (!pDown)
    {
      pDown = pCurrent->resetDown(TileRef{new Tile{down(pos)}});
      m_vpTiles.insert(std::make_pair(down(pos), pDown));
    }

    if (!pLeft)
    {
      pLeft = pCurrent->resetLeft(TileRef{new Tile{left(pos)}});
      m_vpTiles.insert(std::make_pair(left(pos), pLeft));
    }

    if (!pRight)
    {
      pRight = pCurrent->resetRight(TileRef{new Tile{right(pos)}});
      m_vpTiles.insert(std::make_pair(right(pos), pRight));
    }

    updateLinks(pUp);
    updateLinks(pDown);
    updateLinks(pLeft);
    updateLinks(pRight);
  }

  void
  Player::updateLinks(const TileRef& pCurrent)
  {
    Position pos = pCurrent->getPosition();

    {
      auto it = m_vpTiles.find(up(pos));
      if (it != m_vpTiles.end())
      {
        pCurrent->resetUp(it->second);
        it->second->resetDown(pCurrent);
      }
    }

    {
      auto it = m_vpTiles.find(down(pos));
      if (it != m_vpTiles.end())
      {
        pCurrent->resetDown(it->second);
        it->second->resetUp(pCurrent);
      }
    }

    {
      auto it = m_vpTiles.find(left(pos));
      if (it != m_vpTiles.end())
      {
        pCurrent->resetLeft(it->second);
        it->second->resetRight(pCurrent);
      }
    }

    {
      auto it = m_vpTiles.find(right(pos));
      if (it != m_vpTiles.end())
      {
        pCurrent->resetRight(it->second);
        it->second->resetLeft(pCurrent);
      }
    }
  }

  Action
  Player::goHome()
  {
    Logger::getInstance().log("GOING HOME!!!!!!!!\n");

    if (m_vPathHome.empty())
      return CLIMB;

    const auto& pNext = m_vPathHome.back();
    m_vPathHome.pop_back();

    TileRef pUp     = m_pCurrent->getUp();
    TileRef pDown   = m_pCurrent->getDown();
    TileRef pLeft   = m_pCurrent->getLeft();
    TileRef pRight  = m_pCurrent->getRight();

    if (pUp == pNext)
      return turn(UP);

    if (pDown == pNext)
      return turn(DOWN);

    if (pLeft == pNext)
      return turn(LEFT);

    if (pRight == pNext)
      return turn(RIGHT);

    return CLIMB;
  }

  Action
  Player::turn(const Orientation& o)
  {
    /*
     * Print path home
     */
    std::stringstream sText;
    sText << ">>> Updated path home:";
    for (const auto& c : m_vPathHome)
    {
      sText << " [" << c->getPosition().x() << ","
            << c->getPosition().y() << "]";
    }

    sText << "\n";

    Logger::getInstance().log(sText.str().c_str());


    if (o == m_eOrientation)
    {
      m_actions.push(FORWARD);
    }
    else if ((o == UP && m_eOrientation == DOWN) ||
             (o == DOWN && m_eOrientation == UP) ||
             (o == LEFT && m_eOrientation == RIGHT) ||
             (o == RIGHT && m_eOrientation == LEFT))
    {
      m_actions.push(TURN_LEFT);
      m_actions.push(TURN_LEFT);
      m_actions.push(FORWARD);
    }
    else if ((o == UP && m_eOrientation == LEFT) ||
             (o == LEFT && m_eOrientation == DOWN) ||
             (o == DOWN && m_eOrientation == RIGHT) ||
             (o == RIGHT && m_eOrientation == UP))
    {
      m_actions.push(TURN_LEFT);
      m_actions.push(FORWARD);
    }
    else
    {
      m_actions.push(TURN_RIGHT);
      m_actions.push(FORWARD);
    }

    Action next = m_actions.front();
    m_actions.pop();

    return doNext(next);
  }

  Action
  Player::doNext(const Action& next)
  {
    switch (next)
    {
      case TURN_LEFT:
        m_eOrientation = static_cast<Orientation> ((m_eOrientation + 3) % 4);
        break;
      case TURN_RIGHT:
        m_eOrientation = static_cast<Orientation> ((m_eOrientation + 1) % 4);
        break;
      case FORWARD:
        m_pLast = m_pCurrent;
        if (m_eOrientation == UP)
          m_pCurrent = m_pCurrent->getUp();
        else if (m_eOrientation == DOWN)
          m_pCurrent = m_pCurrent->getDown();
        else if (m_eOrientation == LEFT)
          m_pCurrent = m_pCurrent->getLeft();
        else
          m_pCurrent = m_pCurrent->getRight();
        break;
    }

    return next; 
  }

  void
  Player::checkWumpusLocation(std::vector<Choice>& v)
  {
    if (m_wumpus.size() == 0)
    {
      m_wumpus.swap(v);
      return;
    }

    auto it = v.begin();
    while (it != v.end())
    {
      bool bFound = false;

      auto ref = m_wumpus.begin();
      for (; ref != m_wumpus.end(); ++ref)
        if (ref->first == it->first)
          bFound = true;

      if (!bFound)
      {
        m_wumpus.push_back(*it);
        it = v.erase(it);
      }
      else
      {
        ++it;
      }
    }
  }

  Action
  Player::killWumpus(const Orientation& o)
  {
    if (o == m_eOrientation)
    {
      m_actions.push(SHOOT);
    }
    else if ((o == UP && m_eOrientation == DOWN) ||
             (o == DOWN && m_eOrientation == UP) ||
             (o == LEFT && m_eOrientation == RIGHT) ||
             (o == RIGHT && m_eOrientation == LEFT))
    {
      m_actions.push(TURN_LEFT);
      m_actions.push(TURN_LEFT);
      m_actions.push(SHOOT);
    }
    else if ((o == UP && m_eOrientation == LEFT) ||
             (o == LEFT && m_eOrientation == DOWN) ||
             (o == DOWN && m_eOrientation == RIGHT) ||
             (o == RIGHT && m_eOrientation == UP))
    {
      m_actions.push(TURN_LEFT);
      m_actions.push(SHOOT);
    }
    else
    {
      m_actions.push(TURN_RIGHT);
      m_actions.push(SHOOT);
    }

    Action next = m_actions.front();
    m_actions.pop();

    return doNext(next);
  }

  void
  Player::addToPathHome(const TileRef& pCurrent)
  {
    const auto end = m_vPathHome.end();
    auto it = m_vPathHome.begin();

    bool bFound = false;

    for (; it != end; ++it)
    {
      if (*it == pCurrent)
      {
        m_vPathHome.erase(it, end);
        bFound = true;
        break;
      }
    }

    if (!bFound)
      m_vPathHome.push_back(m_pCurrent);
  }

  void
  Player::setPrintCb(const PrintCb& printCb) noexcept
  {
    m_printCb = printCb;
  }
}
