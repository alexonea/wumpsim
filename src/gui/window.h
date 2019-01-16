/*
 *  window.h
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

#ifndef SRC_GUI_WINDOW_H
#define SRC_GUI_WINDOW_H 1

#include <ncurses.h>

namespace wumpus
{
  class Window
  {
  public:
    Window(unsigned x, unsigned y, unsigned w, unsigned h);
    Window(WINDOW* pWindow);

    Window(const Window& other) = delete;
    Window& operator=(const Window& other) = delete;

    Window(Window&& other);
    Window& operator=(Window&& other);
    
    virtual ~Window();

    virtual void refresh() const;
  protected:
    WINDOW* m_pWindow;
    unsigned m_nHeight;
  private:
    bool    m_bManaged;
  };
}

#endif
