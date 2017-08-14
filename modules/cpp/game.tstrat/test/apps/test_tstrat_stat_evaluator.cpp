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
#include <nyra/game/tstrat/Stats.h>
#include <nyra/game/tstrat/StatEvaluator.h>
#include <nyra/test/Test.h>

namespace nyra
{
namespace game
{
namespace tstrat
{
TEST(StatEvaluator, Values)
{
    Stats previous;
    StatEvaluator eval;

    for (size_t ii = 1; ii < 101; ++ii)
    {
        EXPECT_GT(eval.agility(ii), eval.agility(ii - 1));
        EXPECT_GT(eval.constitution(ii), eval.constitution(ii - 1));
        EXPECT_GT(eval.dexterity(ii), eval.dexterity(ii - 1));
        EXPECT_GT(eval.evasionMelee(ii), eval.evasionMelee(ii - 1));
        EXPECT_GT(eval.evasionRanged(ii), eval.evasionRanged(ii - 1));
        EXPECT_GT(eval.luck(ii), eval.luck(ii - 1));
        EXPECT_GT(eval.movement(ii), eval.movement(ii - 1));
        EXPECT_GT(eval.perception(ii), eval.perception(ii - 1));
        EXPECT_GT(eval.speed(ii), eval.speed(ii - 1));

        // Not set
        EXPECT_EQ(0.0, eval.block(ii));
        EXPECT_EQ(0.0, eval.charisma(ii));
        EXPECT_EQ(0.0, eval.fortitude(ii));
        EXPECT_EQ(0.0, eval.resolve(ii));
        EXPECT_EQ(0.0, eval.strength(ii));
        EXPECT_EQ(0.0, eval.stamina(ii));
    }
}
}
}
}

NYRA_TEST()
