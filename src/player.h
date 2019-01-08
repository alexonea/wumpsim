/*
 *  player.h
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

#ifndef SRC_PLAYER_H
#define SRC_PLAYER_H 1

#include <cstdint>

namespace wumpus
{
  enum Sensor
  {
    BREEZE = 0,
    STENCH,
    GLTTER,
    ROAR,
    BUMP,
  };

  enum PlayerOrientation
  {
    UP,
    DOWN,
    LEFT,
    RIGHT,
  };

  struct SensorData
  {
    std::uint8_t data;

    SensorData() : data{0} {};

    SensorData& set       (Sensor sensor) noexcept;
    SensorData& clear     (Sensor sensor) noexcept;
    bool        isActive  (Sensor sensor) const noexcept;
  };

  class Player
  {
  public:
    Player(PlayerOrientation eOrientation, unsigned nArrows = 1) noexcept;
    Player(unsigned nArrows = 1) noexcept;

    void updateSensors(const SensorData& sensors) noexcept;
  private:
    unsigned          m_nArrows;
    SensorData        m_sensors;
    PlayerOrientation m_eOrientation;
  };
}

#endif
