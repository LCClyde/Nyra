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
#include <nyra/mtg/Card.h>
#include <nyra/core/String.h>

namespace
{
//===========================================================================//
std::string combineTreeArray(const nyra::mem::Tree<std::string>& tree,
                             const std::string& name)
{
    std::string ret;
    for (size_t ii = 0; ii < tree[name].loopSize(); ++ii)
    {
        if (ii > 0)
        {
            ret += " ";
        }
        ret += tree[name][ii].get();
    }
    return ret;
}

//===========================================================================//
const static size_t SPECIAL_VALUE = std::numeric_limits<size_t>::max();

}

namespace nyra
{
namespace mtg
{
//===========================================================================//
Card::Card() :
    rarity(COMMON),
    power(0),
    toughness(0),
    loyalty(0),
    isFlipCard(false),
    isBackside(false)
{
}

//===========================================================================//
Card::Card(const mem::Tree<std::string>& tree) :
    power(0),
    toughness(0),
    loyalty(0),
    isFlipCard(false),
    isBackside(false)
{
    name = tree["name"].get();
    cost = stringToMana(tree.has("manaCost") ? tree["manaCost"].get() : "");
    text = tree.has("text") ? tree["text"].get() : "";
    rarity = stringToRarity(tree["rarity"].get());
    supertypes = stringToSupertype(tree.has("supertypes") ?
            combineTreeArray(tree, "supertypes") : "");
    types = stringToType(tree.has("types") ?
            combineTreeArray(tree, "types") : "");

    if (tree.has("subtypes"))
    {
        for (size_t ii = 0; ii < tree["subtypes"].loopSize(); ++ii)
        {
            subtypes.push_back(tree["subtypes"][ii].get());
        }
    }

    if (tree.has("power"))
    {
        try
        {
            power = core::str::toType<size_t>(tree["power"].get());
        }
        catch (...)
        {
            power = SPECIAL_VALUE;
        }
    }

    if (tree.has("toughness"))
    {
        try
        {
            toughness = core::str::toType<size_t>(tree["toughness"].get());
        }
        catch (...)
        {
            toughness = SPECIAL_VALUE;
        }
    }

    if (tree.has("loyalty"))
    {
        loyalty = core::str::toType<size_t>(tree["loyalty"].get());
    }

    if (tree.has("names"))
    {
        isFlipCard = true;
        if (name == tree["names"][tree["names"].loopSize() - 1].get())
        {
            isBackside = true;
        }
    }
}

//===========================================================================//
bool Card::hasCost() const
{
    return !(cost.size() == 1 && cost[0] == NONE);
}

//===========================================================================//
bool Card::isType(Type type) const
{
    for (size_t ii = 0; ii < types.size(); ++ii)
    {
        if (types[ii] == type)
        {
            return true;
        }
    }

    return false;
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os, const Card& card)
{
    os << "Name: " << card.name << "\n";

    if (card.hasCost())
    {
        os << "Cost: " << manaToString(card.cost) << "\n";
    }

    if (!card.text.empty())
    {
        os << "Text:\n" << card.text << "\n";
    }

    os << "Rarity: " << rarityToString(card.rarity) << "\n";

    if (!card.supertypes.empty())
    {
        os << "Supertype: " << supertypeToString(card.supertypes) << "\n";
    }

    os  << "Type: " << typeToString(card.types);

    if (!card.subtypes.empty())
    {
       os << "\nSubtype: " ;
       for (size_t ii = 0; ii < card.subtypes.size(); ++ii)
       {
           if (ii > 0)
           {
               os << " ";
           }
           os << card.subtypes[ii];
       }
    }

    if (card.isType(CREATURE))
    {
        os << "\nPower: ";
        if (card.power == SPECIAL_VALUE)
        {
            os << "*\n";
        }
        else
        {
            os << card.power << "\n";
        }

        os << "Toughness: ";
        if (card.toughness == SPECIAL_VALUE)
        {
            os << "*";
        }
        else
        {
            os << card.toughness;
        }
    }

    if (card.isType(PLANESWALKER))
    {
        os << "\nLoyalty: " << card.loyalty;
    }

    return os;
}
}
}
