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
#include <nyra/test/Test.h>

nyra::game::twod::Stats createStats()
{
    nyra::game::twod::Stats stats;
    stats.movement = 1;
    stats.agility = 2;
    stats.evasion = 3;
    stats.dexterity = 4;
    stats.strength = 5;
    stats.constitution = 6;
    stats.fortitude = 7;
    stats.stamina = 8;
    stats.perception = 9;
    stats.speed = 10;
    stats.luck = 11;
    stats.charisma = 12;
    stats.block = 13;
    stats.resolve = 14;
    return stats;
}

namespace nyra
{
namespace game
{
namespace twod
{
TEST(Stats, Construct)
{
    const Stats stats;
    EXPECT_EQ(static_cast<uint8_t>(0), stats.movement);
    EXPECT_EQ(static_cast<uint8_t>(0), stats.agility);
    EXPECT_EQ(static_cast<uint8_t>(0), stats.evasion);
    EXPECT_EQ(static_cast<uint8_t>(0), stats.dexterity);
    EXPECT_EQ(static_cast<uint8_t>(0), stats.strength);
    EXPECT_EQ(static_cast<uint8_t>(0), stats.constitution);
    EXPECT_EQ(static_cast<uint8_t>(0), stats.fortitude);
    EXPECT_EQ(static_cast<uint8_t>(0), stats.stamina);
    EXPECT_EQ(static_cast<uint8_t>(0), stats.perception);
    EXPECT_EQ(static_cast<uint8_t>(0), stats.speed);
    EXPECT_EQ(static_cast<uint8_t>(0), stats.luck);
    EXPECT_EQ(static_cast<uint8_t>(0), stats.charisma);
    EXPECT_EQ(static_cast<uint8_t>(0), stats.block);
    EXPECT_EQ(static_cast<uint8_t>(0), stats.resolve);
}

TEST(Stats, Archive)
{
    const Stats stats(createStats());
    const Stats archived = test::archive(stats);
    EXPECT_EQ(stats.movement, archived.movement);
    EXPECT_EQ(stats.agility, archived.agility);
    EXPECT_EQ(stats.evasion, archived.evasion);
    EXPECT_EQ(stats.dexterity, archived.dexterity);
    EXPECT_EQ(stats.strength, archived.strength);
    EXPECT_EQ(stats.constitution, archived.constitution);
    EXPECT_EQ(stats.fortitude, archived.fortitude);
    EXPECT_EQ(stats.stamina, archived.stamina);
    EXPECT_EQ(stats.perception, archived.perception);
    EXPECT_EQ(stats.speed, archived.speed);
    EXPECT_EQ(stats.luck, archived.luck);
    EXPECT_EQ(stats.charisma, archived.charisma);
    EXPECT_EQ(stats.block, archived.block);
    EXPECT_EQ(stats.resolve, archived.resolve);
}

TEST(Stats, Stdout)
{
    const Stats stats(createStats());
    const std::string expected =
            "Movement:     1\n"
            "Agility:      2\n"
            "Evasion:      3\n"
            "Dexterity:    4\n"
            "Strength:     5\n"
            "Constitution: 6\n"
            "Fortitude:    7\n"
            "Stamina:      8\n"
            "Perception:   9\n"
            "Speed:        10\n"
            "Luck:         11\n"
            "Charisma:     12\n"
            "Block:        13\n"
            "Resolve:      14";
    EXPECT_EQ(test::stdout(stats), expected);
}
}
}
}

NYRA_TEST()
