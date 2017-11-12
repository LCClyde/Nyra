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
#include <iostream>
#include <nyra/mtg/Set.h>
#include <nyra/json/JSON.h>


namespace nyra
{
namespace mtg
{
//===========================================================================//
Set::Set(const std::string& jsonPathname)
{
    json::JSON tree;
    core::read(jsonPathname, tree);

    const auto& cards = tree["cards"];
    for (size_t ii = 0; ii < cards.loopSize(); ++ii)
    {
        Card card(cards[ii]);

        if (card.isBackside)
        {
            mBacksides.push_back(card);
        }
        else
        {
            mCards.push_back(card);
        }
    }
}

//===========================================================================//
void Set::addSet(const Set& other)
{
    for (const Card& card : other.mCards)
    {
        mCards.push_back(card);
    }

    for (const Card& card : other.mBacksides)
    {
        mBacksides.push_back(card);
    }
}

//===========================================================================//
Set Set::filterRarity(const std::vector<Rarity>& rarity) const
{
    Set set;

    for (const Card& card : mCards)
    {
        if (std::find(rarity.begin(),
                      rarity.end(),
                      card.rarity) != rarity.end())
        {
            set.mCards.push_back(card);
        }
    }

    return set;
}

//===========================================================================//
Set Set::filterEDHColor(const std::vector<Mana>& colors) const
{
    Set set;

    for (const Card& card : mCards)
    {
        const std::vector<Mana>& edh = card.getEDHColors();
        bool match = true;

        for (const Mana& color : edh)
        {
            // Special case for colorless. It goes in any color
            if (edh.empty())
            {
                continue;
            }

            // If this card is more colors we don't need to search.
            if (edh.size() > colors.size())
            {
                match = false;
                continue;
            }

            if (std::find(colors.begin(),
                          colors.end(),
                          color) == colors.end())
            {
                match = false;
            }
        }

        if (match)
        {
            set.mCards.push_back(card);
        }
    }

    return set;
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os, const Set& set)
{
    const std::vector<Card> cards = set.getAllCards();

    for (size_t ii = 0; ii < cards.size(); ++ii)
    {
        if (ii > 0)
        {
            os << "\n";
        }
        os << cards[ii].name;
    }
    return os;
}
}
}
