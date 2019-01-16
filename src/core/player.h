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
#include <core/guess.h>
#include <core/agent.h>

#include <map>

namespace wumpus
{
  class Player : public Agent
  {
  public:
    Player(Orientation eOrientation, unsigned nArrows = 1) noexcept;
    Player(unsigned nArrows = 1) noexcept;

    void        updateSensors (const Percept& sensors) noexcept;

    Orientation getOrientation() const noexcept;
    void        setOrientation(const Orientation& eOrientation) noexcept;

    unsigned    getArrows     () const noexcept;
    void        setArrows     (unsigned nArrows) noexcept;

    void        setPrintCb    (const PrintCb& printCb) noexcept;
  private:
    unsigned    m_nArrows;
    Percept     m_sensors;
    Orientation m_eOrientation;

    virtual Action doNextAction() override;

    std::map<Position, TileRef> m_vpTiles;
    TileRef                     m_pCurrent;
    PrintCb                     m_printCb;

    void markSafeAround(const TileRef& pCurrent, const Guess& eGuess = OK);
    void updateLinks   (const TileRef& pCurrent);
  };
}


#endif
