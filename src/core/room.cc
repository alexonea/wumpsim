/*
 *  room.cc
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

#include <core/room.h>

#include <core/player.h>

#include <gui/logger.h>
#include <gui/graphics.h>
#include <iostream>

namespace wumpus
{
  Room::Room(const RoomContent& eContent) noexcept
  : m_eContent{eContent}
  {}

  void
  Room::setPlayer(PlayerPtr&& pPlayer)
  {
    m_pPlayer = std::move(pPlayer);
  }

  PlayerPtr&&
  Room::releasePlayer()
  {
    return std::move(m_pPlayer);
  }

  bool
  Room::hasPlayer()
  {
    return (m_pPlayer.get() != nullptr);
  }

  void
  Room::setContent(const RoomContent& eContent) noexcept
  {
    m_eContent = eContent;
  }

  bool
  Room::update()
  {
    if (!m_pPlayer)
      return true;

    applySensors();
    Action action = m_pPlayer->nextAction();
    Logger::getInstance().log("Got action %d\n", action);

    switch (action)
    {
      case FORWARD:
      {
        Logger::getInstance().log("CHANGED PLAYER LOCATION\n");
        Logger::getInstance().log("checking up: %p\n", m_pUp.get());
        Logger::getInstance().log("checking down: %p\n", m_pDown.get());
        Logger::getInstance().log("checking left: %p\n", m_pLeft.get());
        Logger::getInstance().log("checking right: %p\n", m_pRight.get());


        Graphics::getInstance().waitForKey();

        RoomPtr pNextRoom;
        PlayerOrientation orientation = m_pPlayer->getOrientation();
        
        if (orientation == UP && m_pUp)
          pNextRoom = std::static_pointer_cast<Room> (m_pUp);
        else if (orientation == DOWN && m_pDown)
          pNextRoom = std::static_pointer_cast<Room> (m_pDown); 
        else if (orientation == LEFT && m_pLeft)
          pNextRoom = std::static_pointer_cast<Room> (m_pLeft);
        else if (m_pRight)
          pNextRoom = std::static_pointer_cast<Room> (m_pRight);

        if (pNextRoom)
        {
          pNextRoom->m_pPlayer = std::move(m_pPlayer);
        }
        else
          return false;

        break;
      }
    }

    return true;
  }

  void
  Room::applySensors()
  {
    RoomPtr pLeft   = std::static_pointer_cast<Room>(getLeft());
    RoomPtr pRight  = std::static_pointer_cast<Room>(getRight());
    RoomPtr pUp     = std::static_pointer_cast<Room>(getUp());
    RoomPtr pDown   = std::static_pointer_cast<Room>(getDown());

    Percept sens;

    if ((pLeft && pLeft->m_eContent == WUMPUS) ||
        (pRight && pRight->m_eContent == WUMPUS) ||
        (pUp && pUp->m_eContent == WUMPUS) ||
        (pDown && pDown->m_eContent == WUMPUS))
      sens.set(STENCH);

    if ((pLeft && pLeft->m_eContent == PIT) ||
        (pRight && pRight->m_eContent == PIT) ||
        (pUp && pUp->m_eContent == PIT) ||
        (pDown && pDown->m_eContent == PIT))
      sens.set(BREEZE);

    if (m_eContent == GOLD)
      sens.set(GLITTER);

    m_pPlayer->updateSensors(sens);
  }
}
