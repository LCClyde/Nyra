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
#include <nyra/mtg/Shandalar.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace mtg
{
//===========================================================================//
void Shandalar::newGame(const std::vector<std::string>& sets)
{
    std::cout << "Starting new game\n";
    for (const std::string& set : sets)
    {
        std::cout << "Loading set: " << set << "\n";
        Set thisSet(core::path::join(core::DATA_PATH, "docs/" + set + ".json"));
        mPool.addSet(thisSet);
    }

    std::cout << "Generating player cards\n";
    mPlayer = mPool.generateBooster(70, 17, 3, 0);
}

//===========================================================================//
void Shandalar::writePlayerCards(const std::string& pathname) const
{
    std::cout << "Writing player cards to: " << pathname << "\n";
    std::ofstream stream(pathname);
    std::vector<std::string> cards;

    for (const Card& card : mPlayer.getAllCards())
    {
        cards.push_back(card.name);
    }

    std::sort(cards.begin(), cards.end());

    for (const std::string& card : cards)
    {
        stream << card << "\n";
    }
}
}
}
