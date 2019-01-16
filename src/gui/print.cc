/*
 *  print.cc
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

#include <gui/print.h>

#include <core/path.h>

#include <vector>
#include <gui/box.h>
#include <gui/graphics.h>
#include <gui/logger.h>

#include <algorithm>
#include <stack>

#include <iostream>

namespace wumpus
{
  static
  unsigned
  toChar(PlayerOrientation eOrientation)
  {
    switch (eOrientation)
    {
      case UP:
        return ACS_UARROW;
      case DOWN:
        return ACS_DARROW;
      case LEFT:
        return ACS_LARROW;
      case RIGHT: 
        return ACS_RARROW;
      default:
        return ' ';
    }

    return ' ';
  }

  static
  bool
  beenVisited(Path* ptr, const std::vector<Path*>& v)
  {
    auto it = std::find(v.begin(), v.end(), ptr);
    return (it != v.end());
  }

  void
  print(const PathPtr& pCurrent, PlayerOrientation eOrientation)
  {
    const unsigned OFFSETX = 30;
    const unsigned OFFSETY = 10;

    std::vector<Box> vBoxes;

    Position p = pCurrent->getRelativePos();

    unsigned currentX = p.first * 6;
    unsigned currentY = p.second * 10;
    vBoxes.push_back(std::move(Box{OFFSETX + currentX, OFFSETY + currentY}));

    Logger::getInstance().log("player location is (%d, %d)\n", currentX, currentY);

    vBoxes[0].setGuess(pCurrent->getGuess());
    vBoxes[0].setPlayer(toChar(eOrientation));

    std::vector<Path*> visited;
    std::stack<Path*> todo;

    Path* pLeft   = static_cast<Path*>(pCurrent->getLeftRaw());
    Path* pRight  = static_cast<Path*>(pCurrent->getRightRaw());
    Path* pUp     = static_cast<Path*>(pCurrent->getUpRaw());
    Path* pDown   = static_cast<Path*>(pCurrent->getDownRaw());

    Logger::getInstance().log("printing now...\n");

    if (pLeft)
      todo.push(pLeft);

    if (pRight)
      todo.push(pRight);

    if (pUp)
      todo.push(pUp);

    if (pDown)
      todo.push(pDown);

    visited.push_back(pCurrent.get());

    while (!todo.empty())
    {
      Path* p = todo.top();
      todo.pop();

      auto it = std::find(visited.begin(), visited.end(), p);
      if (it != visited.end())
        continue;

      Position pos = p->getRelativePos();
      unsigned currentX = pos.first * 6;
      unsigned currentY = pos.second * 10;

      Logger::getInstance().log("Print LOCATION: (%d,%d)\n", currentX, currentY);

      Box box{OFFSETX + currentX, OFFSETY + currentY};
      box.setGuess(p->getGuess());

      vBoxes.push_back(std::move(box));

      visited.push_back(p);

      Path* pLeft   = static_cast<Path*>(p->getLeftRaw());
      Path* pRight  = static_cast<Path*>(p->getRightRaw());
      Path* pUp     = static_cast<Path*>(p->getUpRaw());
      Path* pDown   = static_cast<Path*>(p->getDownRaw());

      if (pLeft)
        todo.push(pLeft);

      if (pRight)
        todo.push(pRight);

      if (pUp)
        todo.push(pUp);

      if (pDown)
        todo.push(pDown);      
    }

    for (const auto& box : vBoxes)
    {
      box.refresh();
    }
  }
}
