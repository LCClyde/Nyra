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
#include <nyra/game/tstrat/StatEvaluator.h>
#include <nyra/math/PolyFit.h>

namespace nyra
{
namespace game
{
namespace tstrat
{
//===========================================================================//
StatEvaluator::StatEvaluator() :
    movement(math::polyFit({1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, 1)),
    agility(math::polyFit({0, 50, 100}, {0, 75, 100}, 2)),
    evasionMelee(math::polyFit({0, 50, 100}, {0, 7, 10}, 2)),
    evasionRanged(math::polyFit({0, 50, 100}, {0, 3, 5}, 2)),
    dexterity(math::polyFit({0, 50, 100}, {0, 10, 15}, 2)),
    strength(0),
    constitution(math::polyFit({10, 20}, {10, 20}, 1)),
    fortitude(0),
    stamina(0),
    perception(math::polyFit({1, 2, 3, 4, 5}, {2, 4, 6, 8, 10}, 1)),
    speed(math::polyFit({0, 100}, {0, 100}, 1)),
    luck(math::polyFit({0, 50, 100}, {0, 3, 5}, 2)),
    charisma(0),
    block(0),
    resolve(0)
{
}
}
}
}
