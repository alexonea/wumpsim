/*
 *  logger.cc
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

#include <gui/logger.h>
#include <cstdarg>
#include <cstring>

namespace wumpus
{
  Logger::Logger(unsigned height)
  : Window{0, LINES - height, (unsigned) COLS, height}
  {
    wsetscrreg(m_pWindow, 1, height - 1);
    idlok(m_pWindow, TRUE);
    immedok(m_pWindow, TRUE);
    scrollok(m_pWindow, TRUE);
    refresh();
  }

  Logger::~Logger()
  {
    wborder(m_pWindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    refresh();
  }

  void
  Logger::refresh() const
  {
    box(m_pWindow, 0, 0);
    wrefresh(m_pWindow);
  }

  void
  Logger::log(const char *format, ...)
  {
    va_list args;
    va_start(args, format);

    char buff[256];
    vsnprintf(buff, 255, format, args);


    // printw()

    mvwprintw(m_pWindow, m_nHeight - 1, 1, buff);
    refresh();

    va_end(args);
  }

  Logger&
  Logger::getInstance()
  {
    static Logger s_logger{10};
    return s_logger;
  }
}
