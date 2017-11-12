/*
 * Copyright (c) 2016 Clyde Stanfield
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
#include <nyra/test/Test.h>
#include <nyra/mtg/Constants.h>

namespace nyra
{
namespace mtg
{
//===========================================================================//
TEST(Mana, Conversion)
{
    std::vector<std::string> strings =
    {
        "",
        "{0}",
        "{2}{R}{R}",
        "{X}{X}{B}",
        "{W}{U}{B}{R}{G}",
        "{16}"
    };

    std::vector<std::vector<Mana>> manas =
    {
        {NONE},
        {},
        {COLORLESS, COLORLESS, RED, RED},
        {X, X, BLACK},
        {WHITE, BLUE, BLACK, RED, GREEN},
        {COLORLESS, COLORLESS, COLORLESS, COLORLESS,
         COLORLESS, COLORLESS, COLORLESS, COLORLESS,
         COLORLESS, COLORLESS, COLORLESS, COLORLESS,
         COLORLESS, COLORLESS, COLORLESS, COLORLESS}
    };

    std::vector<size_t> cmc = {0, 0, 4, 1, 5, 16};

    for (size_t ii = 0; ii < strings.size(); ++ii)
    {
        EXPECT_EQ(manas[ii], stringToMana(strings[ii]));
        EXPECT_EQ(strings[ii], manaToString(manas[ii]));
        EXPECT_EQ(cmc[ii], getConvertedManaCost(manas[ii]));
    }

    EXPECT_ANY_THROW(stringToMana("foo"));
}

//===========================================================================//
TEST(Rarity, Converstion)
{
    for (size_t ii = 0; ii < MAX_RARITY; ++ii)
    {
        const Rarity rarity = static_cast<Rarity>(ii);
        const std::string name = rarityToString(rarity);
        EXPECT_EQ(rarity, stringToRarity(name));
    }

    EXPECT_ANY_THROW(stringToRarity("foo"));
}

//===========================================================================//
TEST(Type, Converstion)
{
    std::vector<Type> allTypes;
    std::string allNames;

    for (size_t ii = 0; ii < MAX_TYPE; ++ii)
    {
        const std::vector<Type> type = {static_cast<Type>(ii)};
        allTypes.push_back(type[0]);
        const std::string name = typeToString(type);

        if (ii > 0)
        {
            allNames += " ";
        }
        allNames += name;

        EXPECT_EQ(type, stringToType(name));
    }

    EXPECT_EQ(allTypes, stringToType(allNames));
    EXPECT_EQ(allNames, typeToString(allTypes));

    EXPECT_ANY_THROW(stringToType("foo"));
}

//===========================================================================//
TEST(Supertype, Converstion)
{
    std::vector<Supertype> allTypes;
    std::string allNames;

    for (size_t ii = 0; ii < MAX_SUPERTYPE; ++ii)
    {
        const std::vector<Supertype> type = {static_cast<Supertype>(ii)};
        allTypes.push_back(type[0]);
        const std::string name = supertypeToString(type);

        if (ii > 0)
        {
            allNames += " ";
        }
        allNames += name;

        EXPECT_EQ(type, stringToSupertype(name));
    }

    EXPECT_EQ(allTypes, stringToSupertype(allNames));
    EXPECT_EQ(allNames, supertypeToString(allTypes));

    EXPECT_ANY_THROW(stringToType("foo"));
}
}
}

NYRA_TEST()
