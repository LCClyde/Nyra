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
#include <nyra/mtg/Constants.h>
#include <nyra/core/String.h>

namespace
{
//===========================================================================//
std::string getMana(const std::string& name, size_t num)
{
    std::string cost;
    for (size_t ii = 0; ii < num; ++ii)
    {
        cost += "{" + name + "}";
    }
    return cost;
}

//===========================================================================//
void getMana(nyra::mtg::Mana mana,
             size_t num,
             std::vector<nyra::mtg::Mana>& vec)
{
    for (size_t ii = 0; ii < num; ++ii)
    {
        vec.push_back(mana);
    }
}
}

namespace nyra
{
namespace mtg
{
//===========================================================================//
std::string manaToString(const std::vector<Mana>& mana)
{
    if (mana.empty())
    {
        return "{0}";
    }

    if (mana.size() == 1 && mana[0] == NONE)
    {
        return "";
    }

    const std::string costs;

    std::vector<size_t> numMana(MAX_MANA);

    // Don't assume the order
    for (size_t ii = 0; ii < mana.size(); ++ii)
    {
        numMana[mana[ii]] += 1;
    }

    std::string cost;

    if (numMana[COLORLESS] > 0)
    {
        cost += "{" + core::str::toString(numMana[COLORLESS]) + "}";
    }

    cost += getMana("X", numMana[X]);
    cost += getMana("W", numMana[WHITE]);
    cost += getMana("U", numMana[BLUE]);
    cost += getMana("B", numMana[BLACK]);
    cost += getMana("R", numMana[RED]);
    cost += getMana("G", numMana[GREEN]);
    return cost;
}

//===========================================================================//
std::vector<Mana> stringToMana(const std::string& mana)
{
    std::vector<Mana> results;
    if (mana == "{0}")
    {
        return results;
    }

    if (mana.empty())
    {
        results.push_back(NONE);
        return results;
    }

    const std::vector<std::string> symbols = core::str::split(mana, "{");

    std::vector<size_t> numMana(MAX_MANA);
    for (size_t ii = 0; ii < symbols.size(); ++ii)
    {
        if (symbols[ii].empty())
        {
            continue;
        }

        const char symbol = symbols[ii][0];
        if (symbol == 'W')
        {
            numMana[WHITE] += 1;
        }
        else if (symbol == 'U')
        {
            numMana[BLUE] += 1;
        }
        else if (symbol == 'B')
        {
            numMana[BLACK] += 1;
        }
        else if (symbol == 'R')
        {
            numMana[RED] += 1;
        }
        else if (symbol == 'G')
        {
            numMana[GREEN] += 1;
        }
        else if (symbol == 'X')
        {
            numMana[X] += 1;
        }
        else
        {
            const std::string substr =
                    symbols[ii].substr(0, symbols[ii].size() - 1);
            const size_t colorless = core::str::toType<size_t>(substr);
            numMana[COLORLESS] += colorless;
        }
    }

    getMana(COLORLESS, numMana[COLORLESS], results);
    getMana(X, numMana[X], results);
    getMana(WHITE, numMana[WHITE], results);
    getMana(BLUE, numMana[BLUE], results);
    getMana(BLACK, numMana[BLACK], results);
    getMana(RED, numMana[RED], results);
    getMana(GREEN, numMana[GREEN], results);

    return results;
}

//===========================================================================//
size_t getConvertedManaCost(const std::vector<Mana>& mana)
{
    size_t ccm = 0;
    for (size_t ii = 0; ii < mana.size(); ++ii)
    {
        if (mana[ii] != X && mana[ii] != NONE)
        {
            ++ccm;
        }
    }

    return ccm;
}

//===========================================================================//
std::string rarityToString(Rarity rarity)
{
    switch (rarity)
    {
    case BASIC_LAND:
        return "Basic Land";
    case COMMON:
        return "Common";
    case UNCOMMON:
        return "Uncommon";
    case RARE:
        return "Rare";
    case MYTHIC:
        return "Mythic Rare";
    default:
        throw std::runtime_error("Unknown rarity: " +
                core::str::toString<int>(static_cast<int>(rarity)));
    }
}

//===========================================================================//
Rarity stringToRarity(const std::string& rarity)
{
    const std::string lrarity = core::str::lower(rarity);

    if (lrarity == "basic land")
    {
        return BASIC_LAND;
    }
    else if (lrarity == "common")
    {
        return COMMON;
    }
    else if (lrarity == "uncommon")
    {
        return UNCOMMON;
    }
    else if (lrarity == "rare")
    {
        return RARE;
    }
    else if (lrarity == "mythic rare")
    {
        return MYTHIC;
    }
    else
    {
        throw std::runtime_error("Unknown rarity: " + rarity);
    }
}

//===========================================================================//
std::string typeToString(const std::vector<Type>& types)
{
    std::string results;

    for (size_t ii = 0; ii < types.size(); ++ii)
    {
        if (ii > 0)
        {
            results += " ";
        }

        switch (types[ii])
        {
        case ARTIFACT:
            results += "Artifact";
            break;
        case CREATURE:
            results += "Creature";
            break;
        case ENCHANTMENT:
            results += "Enchantment";
            break;
        case INSTANT:
            results += "Instant";
            break;
        case SORCERY:
            results += "Sorcery";
            break;
        case LAND:
            results += "Land";
            break;
        case PLANESWALKER:
            results += "Planeswalker";
            break;
        case TRIBAL:
            results += "Tribal";
            break;
        case CONSPIRACY:
            results += "Conspiracy";
            break;
        case PHENOMENON:
            results += "Phenomenon";
            break;
        case PLANE:
            results += "Plane";
            break;
        case VANGUARD:
            results += "Vanguard";
            break;
        default:
            throw std::runtime_error("Unknown type");
            break;
        }
    }

    return results;
}

//===========================================================================//
std::vector<Type> stringToType(const std::string& type)
{
    const std::vector<std::string> types = core::str::split(type, " ");
    std::vector<Type> results;

    for (const std::string& thisType : types)
    {
        if (thisType.empty())
        {
            continue;
        }

        const std::string ltype = core::str::lower(thisType);

        if (ltype == "artifact")
        {
            results.push_back(ARTIFACT);
        }
        else if (ltype == "creature")
        {
            results.push_back(CREATURE);
        }
        else if (ltype == "enchantment")
        {
            results.push_back(ENCHANTMENT);
        }
        else if (ltype == "instant")
        {
            results.push_back(INSTANT);
        }
        else if (ltype == "sorcery")
        {
            results.push_back(SORCERY);
        }
        else if (ltype == "land")
        {
            results.push_back(LAND);
        }
        else if (ltype == "planeswalker")
        {
            results.push_back(PLANESWALKER);
        }
        else if (ltype == "tribal")
        {
            results.push_back(TRIBAL);
        }
        else if (ltype == "conspiracy")
        {
            results.push_back(CONSPIRACY);
        }
        else if (ltype == "phenomenon")
        {
            results.push_back(PHENOMENON);
        }
        else if (ltype == "plane")
        {
            results.push_back(PLANE);
        }
        else if (ltype == "vanguard")
        {
            results.push_back(VANGUARD);
        }
        else
        {
            throw std::runtime_error("Unknown type: " + type);
        }
    }

    return results;
}

//===========================================================================//
std::vector<Supertype> stringToSupertype(const std::string& types)
{
    const std::vector<std::string> supertypes = core::str::split(types, " ");
    std::vector<Supertype> results;

    for (const std::string& thisType : supertypes)
    {
        if (thisType.empty())
        {
            continue;
        }

        const std::string ltype = core::str::lower(thisType);

        if (ltype == "basic")
        {
            results.push_back(BASIC);
        }
        else if (ltype == "legendary")
        {
            results.push_back(LEGENDARY);
        }
        else if (ltype == "ongoing")
        {
            results.push_back(ONGOING);
        }
        else if (ltype == "snow")
        {
            results.push_back(SNOW);
        }
        else if (ltype == "world")
        {
            results.push_back(WORLD);
        }
        else
        {
            throw std::runtime_error("Unknown Supertype: " + types);
        }
    }

    return results;
}

//===========================================================================//
std::string supertypeToString(const std::vector<Supertype>& types)
{
    std::string results;

    for (size_t ii = 0; ii < types.size(); ++ii)
    {
        if (ii > 0)
        {
            results += " ";
        }

        switch (types[ii])
        {
        case BASIC:
            results += "Basic";
            break;
        case LEGENDARY:
            results += "Legendary";
            break;
        case ONGOING:
            results += "Ongoing";
            break;
        case SNOW:
            results += "Snow";
            break;
        case WORLD:
            results += "World";
            break;
        default:
            throw std::runtime_error("Unknown type");
            break;
        }
    }

    return results;
}
}
}
