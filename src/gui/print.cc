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

#include <core/tile.h>
// #include <core/player.h>

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
  toChar(Orientation eOrientation)
  {
    switch (eOrientation)
    {
      case UP:
        return '^';
      case DOWN:
        return 'v';
      case LEFT:
        return '<';
      case RIGHT: 
        return '>';
      default:
        return ' ';
    }

    return ' ';
  }

  static
  bool
  beenVisited(Tile* ptr, const std::vector<Tile*>& v)
  {
    auto it = std::find(v.begin(), v.end(), ptr);
    return (it != v.end());
  }

  void
  print(const TileRef& pCurrent, Orientation eOrientation, Percept percept)
  {
    const unsigned OFFSETX = 20;
    const unsigned OFFSETY = 20;

    std::vector<Box> vBoxes;

    Position p = pCurrent->getPosition();

    unsigned currentX = p.x() * 6;
    unsigned currentY = p.y() * 10;
    vBoxes.push_back(std::move(Box{OFFSETX + currentX, OFFSETY + currentY}));

    Logger::getInstance().log("player location is (%d, %d)\n", currentX, currentY);

    vBoxes[0].setGuess(*((GuessData*) pCurrent.get()));
    vBoxes[0].setPlayer(toChar(eOrientation));
    vBoxes[0].setPercept(percept);

    std::vector<Tile*> visited;
    std::stack<Tile*> todo;

    Tile* pLeft   = pCurrent->getLeft().get();
    Tile* pRight  = pCurrent->getRight().get();
    Tile* pUp     = pCurrent->getUp().get();
    Tile* pDown   = pCurrent->getDown().get();

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
      Tile* p = todo.top();
      todo.pop();

      auto it = std::find(visited.begin(), visited.end(), p);
      if (it != visited.end())
        continue;

      Position pos = p->getPosition();
      unsigned currentX = pos.x() * 6;
      unsigned currentY = pos.y() * 10;

      Box box{OFFSETX + currentX, OFFSETY + currentY};
      box.setGuess(*((GuessData*) p));

      vBoxes.push_back(std::move(box));

      visited.push_back(p);

      Tile* pLeft   = p->getLeft().get();
      Tile* pRight  = p->getRight().get();
      Tile* pUp     = p->getUp().get();
      Tile* pDown   = p->getDown().get();

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
