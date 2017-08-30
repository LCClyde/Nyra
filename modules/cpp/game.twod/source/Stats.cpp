/*
 * Copyright (c) 2017 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#include <nyra/game/twod/Stats.h>


namespace nyra
{
namespace game
{
namespace twod
{
//===========================================================================//
core::RandomNormal<int16_t> Stats::mDefaultDistribution(50.0, 15.0, 0, 100);

//===========================================================================//
Stats::Stats() :
    movement(0),
    agility(0),
    evasion(0),
    dexterity(0),
    strength(0),
    constitution(0),
    fortitude(0),
    stamina(0),
    perception(0),
    speed(0),
    luck(0),
    charisma(0),
    block(0),
    resolve(0)
{
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os, const Stats& stats)
{
    os << "Movement:     " << static_cast<size_t>(stats.movement) << "\n"
       << "Agility:      " << static_cast<size_t>(stats.agility) << "\n"
       << "Evasion:      " << static_cast<size_t>(stats.evasion) << "\n"
       << "Dexterity:    " << static_cast<size_t>(stats.dexterity) << "\n"
       << "Strength:     " << static_cast<size_t>(stats.strength) << "\n"
       << "Constitution: " << static_cast<size_t>(stats.constitution) << "\n"
       << "Fortitude:    " << static_cast<size_t>(stats.fortitude) << "\n"
       << "Stamina:      " << static_cast<size_t>(stats.stamina) << "\n"
       << "Perception:   " << static_cast<size_t>(stats.perception) << "\n"
       << "Speed:        " << static_cast<size_t>(stats.speed) << "\n"
       << "Luck:         " << static_cast<size_t>(stats.luck) << "\n"
       << "Charisma:     " << static_cast<size_t>(stats.charisma) << "\n"
       << "Block:        " << static_cast<size_t>(stats.block) << "\n"
       << "Resolve:      " << static_cast<size_t>(stats.resolve);
    return os;
}
}
}
}
