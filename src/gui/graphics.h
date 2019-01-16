/*
 *  graphics.h
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

#ifndef SRC_GUI_GRAPHICS_H
#define SRC_GUI_GRAPHICS_H 1

namespace wumpus
{
  class Window;
  class Graphics
  {
  public:
    virtual ~Graphics();

    void     waitForKey(int keyCode = 10);
    unsigned waitNextKey();

    static Graphics& getInstance();
  private:
    Graphics();
    Graphics(const Graphics& other) = delete;
    Graphics& operator=(const Graphics& other) = delete;
  };
}

#endif
