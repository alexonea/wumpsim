/*
 *  player.h
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

#ifndef SRC_CORE_PLAYER_H
#define SRC_CORE_PLAYER_H 1

#include <core/player_decl.h>
#include <core/agent.h>

namespace wumpus
{
  class Player
  {
  public:
    Player(PlayerOrientation eOrientation, unsigned nArrows = 1) noexcept;
    Player(unsigned nArrows = 1) noexcept;

    void    updateSensors(const Percept& sensors) noexcept;

    void    setAgent(AgentPtr&& pAgent);
    Action  nextAction();

    PlayerOrientation getOrientation() const noexcept;
  private:
    unsigned          m_nArrows;
    Percept           m_sensors;
    PlayerOrientation m_eOrientation;
    AgentPtr          m_pAgent;
  };
}


#endif
