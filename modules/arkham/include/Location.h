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
#ifndef __NYRA_ARKHAM_LOCATION_H__
#define __NYRA_ARKHAM_LOCATION_H__

#include <string>
#include <nyra/arkham/Expansion.h>
#include <nyra/core/Archive.h>

namespace nyra
{
namespace arkham
{
/*
 *  \class Location
 *  \brief Represents a single location (not street).
 */
struct Location
{
public:
    /*
     *  \func Constructor
     *  \brief Creates an empty location.
     */
    Location();

    /*
     *  \func Constructor
     *  \brief Creates a Location object
     *
     *  \param name The desired name
     *  \param expansion The desired expansion
     */
    Location(const std::string& name,
             const std::string& expansion);

    Location(const std::string& name,
             const std::string& expansion,
             bool blue,
             bool green,
             bool red,
             bool yellow);

    /*
     *  \var name
     *  \brief The name of the location
     */
    std::string name;

    /*
     *  \var expansion
     *  \brief The release expansion
     */
    Expansion expansion;

    bool blue;
    bool green;
    bool red;
    bool yellow;

private:
    NYRA_SERIALIZE()

    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & BOOST_SERIALIZATION_NVP(name);
        archive & BOOST_SERIALIZATION_NVP(expansion);
        archive & BOOST_SERIALIZATION_NVP(blue);
        archive & BOOST_SERIALIZATION_NVP(green);
        archive & BOOST_SERIALIZATION_NVP(red);
        archive & BOOST_SERIALIZATION_NVP(yellow);
    }

    friend std::ostream& operator<<(std::ostream& os, const Location& location);
};
}
}

#endif
