/*
 *  guess.h
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

#ifndef SRC_CORE_GUESS_H
#define SRC_CORE_GUESS_H 1

#include <string>

namespace wumpus
{
  enum Guess
  {
    OK = 0,
    GUESS_PIT,
    GUESS_WUMPUS
  };

  class GuessData
  {
  public:
    GuessData() noexcept;
    virtual ~GuessData() = default;

    void clear        (const Guess& eContent) noexcept;

    void markSafe     () noexcept;
    bool isSafe       () const noexcept;

    void markPermanent() noexcept;
    bool isPermanent  () const noexcept;

    void markBump     () noexcept;
    bool isBump       () const noexcept;

    bool mayBeWumpus  () const noexcept;
    
    std::string toString() const;
  protected:
    virtual int score () const noexcept;
  private:
    bool m_bBump;
    bool m_bWumpus;
    bool m_bPit;
    bool m_bPermanent;
  };
}

#endif
