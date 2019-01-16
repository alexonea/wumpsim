/*
 *  graphics.cc
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

#include <gui/graphics.h>

#include <ncurses.h>

namespace wumpus
{
  Graphics::Graphics()
  {
    initscr();

    if (has_colors() == TRUE)
      start_color();

    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    refresh();
  }

  Graphics::~Graphics()
  {
    endwin();
  }

  Graphics&
  Graphics::getInstance()
  {
    static Graphics s_instance;
    return s_instance;
  }

  void
  Graphics::waitForKey(int keyCode)
  {
    while (getch() != keyCode);
  }

  unsigned
  Graphics::waitNextKey()
  {
    unsigned key;
    while ((key = getch()) == ERR);

    return key;
  }
}