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
#ifndef __NYRA_MTG_SET_H__
#define __NYRA_MTG_SET_H__

#include <nyra/mtg/Card.h>
#include <nyra/core/Archive.h>

namespace nyra
{
namespace mtg
{
/*
 *  \class Set
 *  \brief Represents a MTG set.
 */
class Set
{
public:
    /*
     *  \func Constructor
     *  \brief Creates an empty set.
     */
    Set() = default;

    /*
     *  \func Constructor
     *  \brief Creates a Set from a pathname
     *
     *  \param pathname The set on disk
     */
    Set(const std::string& pathname);

    /*
     *  \var getAllCards
     *  \brief Gets a list of all the cards in the set
     *
     *  \return The list of cards.
     */
    const std::vector<Card>& getAllCards() const
    {
        return mCards;
    }


private:
    NYRA_SERIALIZE()

    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & BOOST_SERIALIZATION_NVP(mName);
        archive & BOOST_SERIALIZATION_NVP(mCards);
        archive & BOOST_SERIALIZATION_NVP(mBacksides);
    }

    friend std::ostream& operator<<(std::ostream& os, const Set& set);

    std::string mName;
    std::vector<Card> mCards;
    std::vector<Card> mBacksides;
};
}
}

#endif
