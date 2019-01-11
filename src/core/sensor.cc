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

#include <core/sensor.h>

namespace wumpus
{
  template <typename T>
  T&
  SensorData<T>::set(T sensor) noexcept
  {
    data |= (1 << sensor);
    return *this;
  }

  template <typename T>
  T&
  SensorData<T>::clear(T sensor) noexcept
  {
    data &= ~(1 << sensor);
    return *this;
  }

  template <typename T>
  bool
  SensorData<T>::isActive(T sensor) const noexcept
  {
    return (data & (1 << sensor));
  }

  template <typename T>
  bool
  SensorData<T>::isZero() const noexcept
  {
    return (data == 0);
  }
}
