/*
 *  player.cc
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

#include "player.h"

namespace wumpus
{
  SensorData&
  SensorData::set(Sensor sensor) noexcept
  {
    data |= (1 << sensor);
    return *this;
  }

  SensorData&
  SensorData::clear(Sensor sensor) noexcept
  {
    data &= ~(1 << sensor);
    return *this;
  }

  bool
  SensorData::isActive(Sensor sensor) const noexcept
  {
    return (data & (1 << sensor));
  }

  Player::Player(PlayerOrientation eOrientation, unsigned nArrows) noexcept
  : m_eOrientation{eOrientation}
  , m_nArrows{nArrows}
  {}

  Player::Player(unsigned nArrows) noexcept
  : m_eOrientation{RIGHT}
  , m_nArrows{nArrows}
  {}

  void
  Player::updateSensors(const SensorData& sensors) noexcept
  {
    m_sensors = sensors;
  }
}
