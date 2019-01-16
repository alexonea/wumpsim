/*
 *  box.h
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

#ifndef SRC_GUI_BOX_H
#define SRC_GUI_BOX_H 1

#include <core/guess.h>
#include <gui/window.h>

#include <memory>

namespace wumpus
{
  class Box : public Window
  {
  public:
    Box(unsigned x, unsigned y, unsigned w = 11, unsigned h = 7);
    virtual ~Box();

    Box(Box&& other) = default;
    Box& operator=(Box&& other) = default;

    virtual void refresh() const;

    void setGuess(const Guess& guess);
    void setPlayer(unsigned player);
  private:
    unsigned  m_player;
    Guess     m_guess;
    unsigned  m_nWidth;
    unsigned  m_nHeight;
  };

  using BoxPtr = std::shared_ptr<Box>;
}

#endif
