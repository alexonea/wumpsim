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
#include <queue>

namespace wumpus
{
  using Choice = std::pair<TileRef, Orientation>;
  
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
    TileRef                     m_pLast;
    PrintCb                     m_printCb;

    void markSafeAround (const TileRef& pCurrent, const Guess& eGuess = OK);
    void expandAround   (const TileRef& pCurrent);
    void updateLinks    (const TileRef& pCurrent);

    std::vector<Choice> m_wumpus;
    bool                m_bWumpusKilled;
    bool                m_bGoldGrabbed;

    void   checkWumpusLocation(std::vector<Choice>& v);
    Action killWumpus(const Orientation& o);

    std::queue<Action>    m_actions;

    Action goHome   ();
    Action turn     (const Orientation& o);
    Action doNext   (const Action& next);

    std::vector<TileRef>   m_vPathHome;
    void addToPathHome(const TileRef& c);
  };
}


#endif
