/*
 *  box.cc
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

#include <gui/box.h>

#include <core/error.h>

#include <iostream>

namespace wumpus
{
  Box::Box(unsigned x, unsigned y, unsigned w, unsigned h)
  : Window{y, LINES - x - h, w, h}
  , m_nWidth{w}
  , m_nHeight{h}
  , m_player{' '}
  {
    if (w <= 2 || h <= 2)
      throw Error("Box too small");

    // refresh();
  }

  Box::~Box()
  {
    wborder(m_pWindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    refresh();
  }

  void
  Box::refresh() const
  {
    wborder(m_pWindow, 0, 0, 0, 0, ACS_PLUS, ACS_PLUS, ACS_PLUS, ACS_PLUS);

    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);

    wattron(m_pWindow, COLOR_PAIR(3));
    wattron(m_pWindow, A_BOLD);
    mvwaddch(m_pWindow, 3, 5, m_player);
    wattroff(m_pWindow, A_BOLD);
    wattroff(m_pWindow, COLOR_PAIR(3));

    if (!m_guess.isPermanent())
    {
      wattron(m_pWindow, COLOR_PAIR(2));
      wattron(m_pWindow, A_BOLD);
      mvwprintw(m_pWindow, m_nHeight - 2, 1, m_guess.toString().c_str());
      wattroff(m_pWindow, A_BOLD);
      wattroff(m_pWindow, COLOR_PAIR(2));
    }
    else
    {
      wattron(m_pWindow, COLOR_PAIR(1));
      wattron(m_pWindow, A_BOLD);
      mvwprintw(m_pWindow, m_nHeight - 2, 1, m_guess.toString().c_str());
      wattroff(m_pWindow, A_BOLD);
      wattroff(m_pWindow, COLOR_PAIR(1));
    }

    Window::refresh();
  }

  void
  Box::setGuess(const Guess& guess)
  {
    m_guess = guess;
  }

  void
  Box::setPlayer(unsigned player)
  {
    m_player = player;
  }
}
