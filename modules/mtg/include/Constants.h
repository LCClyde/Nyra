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
#ifndef __NYRA_MTG_CONSTANTS_H__
#define __NYRA_MTG_CONSTANTS_H__

#include <string>
#include <vector>

namespace nyra
{
namespace mtg
{
/*
 *  \type Mana
 *  \brief Numerical representation of mana symbols.
 */
enum Mana
{
    NONE = 0,
    COLORLESS,
    X,
    WHITE,
    BLUE,
    BLACK,
    RED,
    GREEN,
    MAX_MANA
};

/*
 *  \func manaToString
 *  \brief Converts a vector of mana symbols into a string of the format:
 *         {2}{R}{R}.
 *
 *  \param mana The cost to convert
 *  \return The string representation.
 */
std::string manaToString(const std::vector<Mana>& mana);

/*
 *  \func stringToMana
 *  \brief Converts a string in the format {2}{R}{R} into an in memory mana
 *         cost.
 *
 *  \param mana The string to covert.
 *  \return The resulting cost.
 */
std::vector<Mana> stringToMana(const std::string& mana);

/*
 *  \func getConvertedManaCost
 *  \brief Gets the converted mana cost. X results in 0.
 *
 *  \param mana The mana cost
 *  \return The converted mana cost.
 */
size_t getConvertedManaCost(const std::vector<Mana>& mana);

/*
 *  \type Rarity
 *  \brief Numerical representation of card rarity.
 */
enum Rarity
{
    BASIC_LAND = 0,
    COMMON,
    UNCOMMON,
    RARE,
    MYTHIC,
    MAX_RARITY
};

/*
 *  \func rarityToString
 *  \brief Converts a string into a rarity.
 *
 *  \param rarity The rarity to covert
 *  \return The result.
 */
std::string rarityToString(Rarity rarity);

/*
 *  \func stringToRarity
 *  \brief Converts a string into a rarity
 *
 *  \param rarity The string to covert
 *  \return The resullt.
 */
Rarity stringToRarity(const std::string& rarity);

/*
 *  \type Type
 *  \brief Numerical representation of card type.
 */
enum Type
{
    ARTIFACT = 0,
    CREATURE,
    ENCHANTMENT,
    INSTANT,
    SORCERY,
    LAND,
    PLANESWALKER,
    TRIBAL,
    CONSPIRACY,
    PHENOMENON,
    PLANE,
    VANGUARD,
    MAX_TYPE
};

/*
 *  \func typeToString
 *  \brief Converts a list of types into a space separated string
 *
 *  \param type The types to convert
 *  \return The result.
 */
std::string typeToString(const std::vector<Type>& type);

/*
 *  \func stringToType
 *  \brief Converts a string into a list of types.
 *
 *  \param type A string of space separated types.
 *  \return The result.
 */
std::vector<Type> stringToType(const std::string& type);

/*
 *  \type Supertype
 *  \brief Numerical representation of card supertypes
 */
enum Supertype
{
    BASIC = 0,
    LEGENDARY,
    ONGOING,
    SNOW,
    WORLD,
    MAX_SUPERTYPE
};

/*
 *  \func supertypeToString
 *  \brief Converts a list of supertypes into a space separated string
 *
 *  \param types The types to convert
 *  \return The result.
 */
std::string supertypeToString(const std::vector<Supertype>& types);

/*
 *  \func stringToSupertype
 *  \brief Converts a string into a list of supertypes.
 *
 *  \param type A string of space separated supertypes.
 *  \return The result.
 */
std::vector<Supertype> stringToSupertype(const std::string& types);
}
}

#endif
