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
#ifndef __NYRA_MTG_CARD_H__
#define __NYRA_MTG_CARD_H__

#include <string>
#include <vector>
#include <nyra/mtg/Constants.h>
#include <nyra/core/Archive.h>
#include <nyra/mem/Tree.h>

namespace nyra
{
namespace mtg
{
/*
 *  \class Card
 *  \brief A class to represent a single Magic card.
 */
struct Card
{
public:
    const static size_t SPECIAL_VALUE = std::numeric_limits<size_t>::max();

    /*
     *  \func Constructor
     *  \brief Sets a blank card.
     */
    Card();

    /*
     *  \func Constructor
     *  \brief Creates a card from mtg json
     *
     *  \param A single card for mtg json
     */
    Card(const mem::Tree<std::string>& tree);

    /*
     *  \fun isType
     *  \brief Returns true if the card has the type.
     *
     *  \param type The desired type
     *  \return True if the card is the type
     */
    bool isType(Type type) const;

    /*
     *  \func hasCost
     *  \brief Returns true if the card has a cost ({0} is a cost). This
     *         only returns false for lands or special cases.
     *
     *  \return True if the card has a cost.
     */
    bool hasCost() const;

    /*
     *  \func equality
     *  \brief Checks if one card is the same as another. This test only
     *         checks the name and assumes all metadata is consistent.
     *
     *  \return True if the cards are the same.
     */
    bool operator==(const Card& other) const
    {
        return name == other.name;
    }

    /*
     *  \func getEDHColors
     *  \brief Attempts to find the true color of a card by looking at it's
     *         intent rather than just it's casting cost. If the card has
     *         a symbol anywhere in it's text it is considered to be that
     *         color.
     *
     *  \return The elder dragon highlander color.
     */
    const std::vector<Mana>& getEDHColors() const;

    /*
     *  \var name
     *  \brief The name of card
     */
    std::string name;

    /*
     *  \var cost
     *  \brief The card's mana cost
     */
    std::vector<Mana> cost;

    /*
     *  \var text
     *  \brief The card text
     */
    std::string text;

    /*
     *  \var rarity
     *  \brief The rarity of the card
     */
    Rarity rarity;

    /*
     *  \var supertypes
     *  \brief Card supertypes (basic and legendary are standard)
     */
    std::vector<Supertype> supertypes;

    /*
     *  \var types
     *  \brief The card types.
     */
    std::vector<Type> types;

    /*
     *  \var subtypes
     *  \brief The card subtypes
     */
    std::vector<std::string> subtypes;

    /*
     *  \var power
     *  \brief The creature power. This is 0 if the card is not a creature.
     */
    size_t power;
    /*
     *  \var toughness
     *  \brief The creature toughness. This is 0 if the card is not a creature.
     */
    size_t toughness;

    /*
     *  \var power
     *  \brief The planeswalker layalty. This is 0 if the card is not
     *         a planeswalker.
     */
    size_t loyalty;

    /*
     *  \var isFlipCard
     *  \brief True if the card has a backside
     */
    bool isFlipCard;

    /*
     *  \var isBackside
     *  \brief True if the card is the backside of another card.
     */
    bool isBackside;

private:
    void removeReminderText();

    NYRA_SERIALIZE()

    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & BOOST_SERIALIZATION_NVP(name);
        archive & BOOST_SERIALIZATION_NVP(cost);
        archive & BOOST_SERIALIZATION_NVP(text);
        archive & BOOST_SERIALIZATION_NVP(rarity);
        archive & BOOST_SERIALIZATION_NVP(supertypes);
        archive & BOOST_SERIALIZATION_NVP(types);
        archive & BOOST_SERIALIZATION_NVP(subtypes);
        archive & BOOST_SERIALIZATION_NVP(power);
        archive & BOOST_SERIALIZATION_NVP(toughness);
        archive & BOOST_SERIALIZATION_NVP(loyalty);
        archive & BOOST_SERIALIZATION_NVP(isFlipCard);
        archive & BOOST_SERIALIZATION_NVP(isBackside);
    }

    friend std::ostream& operator<<(std::ostream& os, const Card& card);

    mutable bool mEDHColorsSet;
    mutable std::vector<Mana> mEDHColors;
};
}
}

#endif
