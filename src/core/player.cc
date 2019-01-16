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

#include <core/tile.h>

namespace wumpus
{
  Player::Player(Orientation eOrientation, unsigned nArrows) noexcept
  : m_eOrientation{eOrientation}
  , m_nArrows{nArrows}
  , m_pCurrent{new Tile}
  {
    m_pCurrent->markSafe();
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
    if (m_pCurrent->isSafe())
      markSafeAround(m_pCurrent);
    else if (!m_sensors.isActive(BREEZE))
      markSafeAround(m_pCurrent, GUESS_PIT);
    else if (!m_sensors.isActive(STENCH))
      markSafeAround(m_pCurrent, GUESS_WUMPUS);

    return CLIMB;
  }

  void
  Player::markSafeAround(const TileRef& pCurrent, const Guess& eGuess)
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

    if (eGuess == OK)
    {
      pUp->markSafe();
      pDown->markSafe();
      pLeft->markSafe();
      pRight->markSafe();
    }
    else
    {
      pUp->clear(eGuess);
      pDown->clear(eGuess);
      pLeft->clear(eGuess);
      pRight->clear(eGuess);
    }
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
}
