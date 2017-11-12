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
#include <nyra/mtg/Card.h>
#include <nyra/core/String.h>

namespace nyra
{
namespace mtg
{
//===========================================================================//
TEST(Card, FromJSON)
{
    mem::Tree<std::string> tree;
    const std::string name = "Shivan Dragon";
    tree["name"] = name;

    const std::string manaCost = "{4}{R}{R}";
    tree["manaCost"] = manaCost;

    const size_t power = 5;
    tree["power"] = core::str::toString(power);

    const size_t toughness = 5;
    tree["toughness"] = core::str::toString(toughness);

    const std::string rarity = "Rare";
    tree["rarity"] = rarity;

    const std::string subtype = "Dragon";
    tree["subtypes"] = subtype;

    const std::string text = "Flying (This creature can't be blocked except"
                             " by creatures with flying or reach.)\n{R}: "
                             "Shivan Dragon gets +1/+0 until end of turn.";
    tree["text"] = text;

    const std::string type = "Creature";
    tree["types"] = type;

    Card card(tree);

    EXPECT_EQ(name, card.name);
    EXPECT_EQ(manaCost, manaToString(card.cost));
    EXPECT_EQ(power, card.power);
    EXPECT_EQ(toughness, card.toughness);
    EXPECT_EQ(card.rarity, stringToRarity(rarity));
    EXPECT_EQ(std::vector<std::string>({subtype}), card.subtypes);
    EXPECT_EQ(text, card.text);
    EXPECT_EQ(type, typeToString(card.types));
    EXPECT_TRUE(card.supertypes.empty());
    EXPECT_FALSE(card.isFlipCard);
    EXPECT_FALSE(card.isBackside);
    EXPECT_EQ(static_cast<size_t>(0), card.loyalty);
}

//===========================================================================//
TEST(Card, isType)
{
    Card card;

    for (size_t ii = 0; ii < MAX_TYPE; ++ii)
    {
        const Type type = static_cast<Type>(ii);
        card.types.clear();
        card.types.push_back(type);
        EXPECT_TRUE(card.isType(type));
    }
}

//===========================================================================//
TEST(Card, hasCost)
{
    Card card;

    // This is 0 cost
    card.cost = {};
    EXPECT_TRUE(card.hasCost());

    card.cost = {COLORLESS, COLORLESS, RED, RED};
    EXPECT_TRUE(card.hasCost());

    card.cost = {X};
    EXPECT_TRUE(card.hasCost());

    card.cost = {NONE};
    EXPECT_FALSE(card.hasCost());
}

//===========================================================================//
TEST(Card, Equality)
{
    Card card;
    card.name = "Name";
    card.cost = {COLORLESS, COLORLESS, RED, RED};
    card.text = "Win the game!";
    card.rarity = MYTHIC;
    card.supertypes = {LEGENDARY, SNOW};
    card.types = {ARTIFACT, CREATURE, LAND};
    card.subtypes = {"Dragon", "Equipment"};
    card.power = 7;
    card.toughness = 11;
    card.loyalty = 3;
    card.isFlipCard = true;
    card.isBackside = true;

    Card other(card);

    EXPECT_EQ(card,other);
}

//===========================================================================//
TEST(Card, EDHColor)
{
    Card card;
    card.cost = {WHITE, GREEN};
    EXPECT_EQ(card.cost, card.getEDHColors());

    card = Card();
    card.cost = {BLACK};
    card.text = "{R}: +1/+0";
    EXPECT_EQ(std::vector<Mana>({BLACK, RED}), card.getEDHColors());
}

//===========================================================================//
TEST(Card, Archive)
{
    Card card;
    card.name = "Name";
    card.cost = {COLORLESS, COLORLESS, RED, RED};
    card.text = "Win the game!";
    card.rarity = MYTHIC;
    card.supertypes = {LEGENDARY, SNOW};
    card.types = {ARTIFACT, CREATURE, LAND};
    card.subtypes = {"Dragon", "Equipment"};
    card.power = 7;
    card.toughness = 11;
    card.loyalty = 3;
    card.isFlipCard = true;
    card.isBackside = true;

    const Card archived = test::archive(card);
    EXPECT_EQ(card.name, archived.name);
    EXPECT_EQ(card.cost, archived.cost);
    EXPECT_EQ(card.text, archived.text);
    EXPECT_EQ(card.rarity, archived.rarity);
    EXPECT_EQ(card.supertypes, archived.supertypes);
    EXPECT_EQ(card.types, archived.types);
    EXPECT_EQ(card.subtypes, archived.subtypes);
    EXPECT_EQ(card.power, archived.power);
    EXPECT_EQ(card.toughness, archived.toughness);
    EXPECT_EQ(card.loyalty, archived.loyalty);
    EXPECT_EQ(card.isFlipCard, archived.isFlipCard);
    EXPECT_EQ(card.isBackside, archived.isBackside);
}


//===========================================================================//
TEST(Card, Stdout)
{
    Card card;
    EXPECT_FALSE(test::stdout(card).empty());
}
}
}

NYRA_TEST()
