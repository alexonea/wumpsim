/*
 *  window.cc
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

#include <gui/window.h>

#include <core/error.h>

#include <iostream>

namespace wumpus
{
  Window::Window(unsigned x, unsigned y, unsigned w, unsigned h)
  : m_pWindow{newwin(h, w, y, x)}
  , m_bManaged{true}
  , m_nHeight{h}
  {
    if (!m_pWindow)
      throw Error("invalid window");
  }

  Window::Window(Window&& other)
  : m_pWindow{other.m_pWindow}
  , m_bManaged{other.m_bManaged}
  , m_nHeight{other.m_nHeight}
  {
    other.m_pWindow = nullptr;
  }

  Window&
  Window::operator=(Window&& other)
  {
    m_pWindow = other.m_pWindow;
    m_bManaged = other.m_bManaged;
    m_nHeight = other.m_nHeight;

    other.m_pWindow = nullptr;
  }

  Window::Window(WINDOW* pWindow)
  : m_pWindow{pWindow}
  , m_bManaged{false}
  {
    if (!m_pWindow)
      throw Error("invalid window");
  }

  Window::~Window()
  {
    if (m_bManaged)
      delwin(m_pWindow);
  }

  void
  Window::refresh() const
  {
    wrefresh(m_pWindow);
  }
}
