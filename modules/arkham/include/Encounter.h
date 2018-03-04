/*
 * Copyright (c) 2018 Clyde Stanfield
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
#ifndef __NYRA_ARKHAM_ENCOUNTER_H__
#define __NYRA_ARKHAM_ENCOUNTER_H__

#include <string>
#include <nyra/arkham/Expansion.h>
#include <nyra/core/Archive.h>

namespace nyra
{
namespace arkham
{
/*
 *  \class Encounter
 *  \brief Represents a location encounter card.
 */
class Encounter
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a blank Encounter.
     */
    Encounter() = default;

    /*
     *  \func Constructor
     *  \brief Creates an Encounter object
     *
     *  \param text The desired text
     *  \param expansion The desired expansion
     */
    Encounter(const std::string& text,
              const std::string& expansion);

    /*
     *  \var text
     *  \brief The text that would be on the card.
     */
    std::string text;

    /*
     *  \var expansion
     *  \brief The release expansion
     */
    Expansion expansion;

private:
    NYRA_SERIALIZE()

    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & BOOST_SERIALIZATION_NVP(text);
        archive & BOOST_SERIALIZATION_NVP(expansion);
    }

    friend std::ostream& operator<<(std::ostream& os,
                                    const Encounter& encounter);
};
}
}

#endif
