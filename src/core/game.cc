/*
 *  game.h
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

#include <core/game.h>

#include <core/player.h>

#include <gui/logger.h>

namespace wumpus
{
  Game::Game(WorldRef&& pWorld) noexcept
  : m_pWorld{std::move(pWorld)}
  , m_iScore{0}
  {}

  void
  Game::setPlayer(PlayerRef&& pPlayer, Position pos) noexcept
  {
    unsigned iPlayerX = m_playerPos.x();
    unsigned iPlayerY = m_playerPos.y();

    RoomContent current = m_pWorld->getRoomType(iPlayerX, iPlayerY);
    if (!current)
      return;

    RoomContent up      = m_pWorld->getRoomType(iPlayerX + 1, iPlayerY);
    RoomContent down    = m_pWorld->getRoomType(iPlayerX - 1, iPlayerY);
    RoomContent left    = m_pWorld->getRoomType(iPlayerX, iPlayerY - 1);
    RoomContent right   = m_pWorld->getRoomType(iPlayerX, iPlayerY + 1);

    m_pPlayer = std::move(pPlayer);
    m_playerPos = pos;

    Percept p;

    if (current == GOLD)
      p.set(GLITTER);

    if (up == WUMPUS || 
        down == WUMPUS || 
        left == WUMPUS || 
        right == WUMPUS)
      p.set(STENCH);

    if (up == PIT || 
        down == PIT || 
        left == PIT || 
        right == PIT)
      p.set(BREEZE);

    m_pPlayer->updateSensors(p);
  }

  bool
  Game::advance()
  {
    Logger::getInstance().log("---> SCORE: %d <---\n", m_iScore);

    Percept p;
    Action next = m_pPlayer->nextAction();

    Orientation o = m_pPlayer->getOrientation();
    
    unsigned iPlayerX = m_playerPos.x();
    unsigned iPlayerY = m_playerPos.y();
    
    RoomContent current = m_pWorld->getRoomType(iPlayerX, iPlayerY);
    RoomContent up      = m_pWorld->getRoomType(iPlayerX + 1, iPlayerY);
    RoomContent down    = m_pWorld->getRoomType(iPlayerX - 1, iPlayerY);
    RoomContent left    = m_pWorld->getRoomType(iPlayerX, iPlayerY - 1);
    RoomContent right   = m_pWorld->getRoomType(iPlayerX, iPlayerY + 1);

    if (next == CLIMB && 
        iPlayerX == 0 && iPlayerY == 0)
      return false;

    if (next == FORWARD)
    {
      if (o == UP && up)
      {
        Logger::getInstance().log("goind UPUPUP\n");
        iPlayerX++;
      }
      else if (o == DOWN && down)
      {
        Logger::getInstance().log("Goind down\n");
        iPlayerX--;
      }
      else if (o == LEFT && left)
      {
        Logger::getInstance().log("Going LEFLEFT\n");
        iPlayerY--;
      }
      else if (o == RIGHT && right)
      {
        Logger::getInstance().log("GOING RIGHT RIGHT!!!\n");
        iPlayerY++;
      }
      else
      {
        Logger::getInstance().log("BUMP DETECTED\n");
        p.set(BUMP);
      }

      Logger::getInstance().log("going forward, orientation=%d\n", o);
      Logger::getInstance().log("up=%d\n", up);
      Logger::getInstance().log("down=%d\n", down);
      Logger::getInstance().log("left=%d\n", left);
      Logger::getInstance().log("right=%d\n", right);
      Logger::getInstance().log("BUMP=%d\n", p.isActive(BUMP));

      if (!p.isActive(BUMP))
      {
        m_playerPos = Position(iPlayerX, iPlayerY);
        
        current = m_pWorld->getRoomType(iPlayerX, iPlayerY);
        up      = m_pWorld->getRoomType(iPlayerX + 1, iPlayerY);
        down    = m_pWorld->getRoomType(iPlayerX - 1, iPlayerY);
        left    = m_pWorld->getRoomType(iPlayerX, iPlayerY - 1);
        right   = m_pWorld->getRoomType(iPlayerX, iPlayerY + 1);        
      }

      m_iScore--;
    }

    if (current == WUMPUS || current == PIT)
    {
      m_iScore -= 1000;
      return false;
    }

    if (current == GOLD)
    {
      if (next == GRAB)
      {
        m_iScore += 1000;
        m_pWorld->setRoomType(EMPTY, iPlayerX, iPlayerY);
      }
      else
        p.set(GLITTER);
    }

    const unsigned nArrows = m_pPlayer->getArrows();
    if (next == SHOOT && nArrows > 0)
    {
      bool bKilled = false;

      if (o == UP && up == WUMPUS)
      {
        m_pWorld->setRoomType(EMPTY, iPlayerX + 1, iPlayerY);
        bKilled = true;
      }
      else if (o == DOWN && down == WUMPUS)
      {
        m_pWorld->setRoomType(EMPTY, iPlayerX - 1, iPlayerY);
        bKilled = true;
      }
      else if (o == LEFT && left == WUMPUS)
      {
        m_pWorld->setRoomType(EMPTY, iPlayerX, iPlayerY - 1);
        bKilled = true;
      }
      else if (right == WUMPUS)
      {
        m_pWorld->setRoomType(EMPTY, iPlayerX, iPlayerY + 1);
        bKilled = true;
      }

      if (bKilled)
        p.set(ROAR);

      m_pPlayer->setArrows(nArrows - 1);
      m_iScore -= 10;
    }

    if (up == WUMPUS || 
        down == WUMPUS || 
        left == WUMPUS || 
        right == WUMPUS)
      p.set(STENCH);

    if (up == PIT || 
        down == PIT || 
        left == PIT || 
        right == PIT)
      p.set(BREEZE);

    m_pPlayer->updateSensors(p);
    return true;
  }

  WorldRef&
  Game::getWorld() noexcept
  {
    return m_pWorld;
  }

  PlayerRef&
  Game::getPlayer() noexcept
  {
    return m_pPlayer;
  }
}
