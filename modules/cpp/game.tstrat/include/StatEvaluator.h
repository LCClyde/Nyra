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
#ifndef __NYRA_GAME_TSTRAT_STAT_EVALUATOR_H__
#define __NYRA_GAME_TSTRAT_STAT_EVALUATOR_H__

#include <nyra/math/Polynomial.h>
#include <nyra/game/tstrat/Stats.h>

namespace nyra
{
namespace game
{
namespace tstrat
{
/*
 *  \class StatEvaluator
 *  \brief Creates polynomials for evaluating stats.
 */
class StatEvaluator
{
public:
    /*
     *  \func Constructor
     *  \brief Creates the default polynomials.
     */
    StatEvaluator();

    math::Polynomial movement;
    math::Polynomial agility;
    math::Polynomial evasionMelee;
    math::Polynomial evasionRanged;
    math::Polynomial dexterity;
    math::Polynomial strength;
    math::Polynomial constitution;
    math::Polynomial fortitude;
    math::Polynomial stamina;
    math::Polynomial perception;
    math::Polynomial speed;
    math::Polynomial luck;
    math::Polynomial charisma;
    math::Polynomial block;
    math::Polynomial resolve;
};
}
}
}

#endif
