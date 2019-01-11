/*
 *  path.h
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

#ifndef SRC_CORE_PATH_H
#define SRC_CORE_PATH_H 1

#include <memory>

#include <core/sensor.h>
#include <core/tile.h>

namespace wumpus
{
  enum PathContent
  {
    UNKNOWN = 0,
    OK,
    PIT,
    WUMPUS,
  };

  using Guess = SensorData<PathContent>;

  class Path : public Tile
  {
  public:
    Path(const PathContent& eGuess = UNKNOWN) noexcept;

    Guess  getGuess() const noexcept;
    void   setGuess(const Guess& eGuess);
  private:
    Guess m_eGuess;
  };

  using PathPtr = std::shared_ptr<Path>;
}

#endif
