/*
 *  sensor.h
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

#ifndef SRC_CORE_SENSOR_H
#define SRC_CORE_SENSOR_H 1

#include <cstdint>
#include <type_traits>

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

  template <typename T>
  struct SensorData
  {
    typedef typename std::underlying_type<T>::type TType;
    static_assert(std::is_enum<T>::value, "SensorData needs enumeration type");
    TType data;

    SensorData(const TType& value = 0) : data{value} {};
    SensorData(const T& value) : data{value} {};

    T&    set       (T sensor) noexcept;
    T&    clear     (T sensor) noexcept;
    bool  isActive  (T sensor) const noexcept;
    bool  isZero    ()         const noexcept;
  };
}

#endif
