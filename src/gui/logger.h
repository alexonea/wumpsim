/*
 *  logger.h
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

#ifndef SRC_GUI_LOGGER_H
#define SRC_GUI_LOGGER_H 1

#include <gui/window.h>
#include <sstream>

#include <string>

namespace wumpus
{
  class Logger : public Window, public std::stringstream
  {
  public:
    virtual ~Logger();

    Logger(const Logger& other) = delete;
    Logger& operator=(const Logger& other) = delete;

    Logger(Logger&& other) = default;
    Logger& operator=(Logger&& other) = default;

    virtual void refresh() const;

    void log(const char *format, ...);

    static Logger& getInstance();
  private:
    Logger(unsigned height);
  };
}

#endif
