/*
 *  autopilot.h
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

#ifndef SRC_CORE_AUTOPILOT_H
#define SRC_CORE_AUTOPILOT_H 1

#include <memory>

#include <core/agent.h>

namespace wumpus
{
  /*
   * [12.01.2018] This needs to be fixed. Fw declared here because of
   *              cross-references between agent.h, sensor.h and autopilot.h
   *
   *              Possible solution is to create fw decl headers for most types
   */
  class Path;
  using PathPtr = std::shared_ptr<Path>;

  class AutoPilot : public Agent
  {
  public:
    AutoPilot() = default;
    virtual ~AutoPilot() = default;
  private:
    virtual Action doNext(const SensorData& sensors) override;

    PathPtr m_pRoot;
  };
}

#endif
