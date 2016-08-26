/*
 * Copyright (c) 2016 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
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
#ifndef __NYRA_CORE_COLOR_H__
#define __NYRA_CORE_COLOR_H__

#include <stdint.h>
#include <nyra/core/Archive.h>

namespace nyra
{
namespace core
{
/*
 *  \class Color
 *  \brief Represents an RGBA color.
 */
class Color
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a default (all 0, with 255 alpha) color.
     */
    Color();

    /*
     *  \func Constructor
     *  \brief Creates an RGB color. The alpha is set to 255.
     *
     *  \param r The red value
     *  \param g The green value
     *  \param b The blue value
     */
    Color(uint8_t r, uint8_t g, uint8_t b);

    /*
     *  \func Constructor
     *  \brief Creates an RGBA color.
     *
     *  \param r The red value
     *  \param g The green value
     *  \param b The blue value
     *  \param a The alpha value
     */
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    /*
     *  \func toRGBA
     *  \brief Creates a single value to represent RGBA
     *
     *  \return A single where RGBA = 0xRRGGBBAA
     */
    uint32_t toRGBA() const;

    /*
     *  \func toARGB
     *  \brief Creates a single value to represent ARGB
     *
     *  \return A single where ARGB = 0xAARRGGBB
     */
    uint32_t toARGB() const;

    /*
     *  \func operator Equal
     *  \brief Checks is two Color objects are the same.
     *
     *  \param other The color to test against.
     *  \return True if the colors are the same.
     */
    bool operator==(const Color& other) const
    {
        return r == other.r &&
               g == other.g &&
               b == other.b &&
               a == other.a;
    }

    /*
     *  \func operator Not Equal
     *  \brief Checks is two Color objects are different.
     *
     *  \param other The color to test against.
     *  \return True if the colors are different.
     */
    bool operator!=(const Color& other) const
    {
        return !((*this) == other);
    }

    /*
     *  \var r
     *  \brief The red value in the range of 0-255
     */
    uint8_t r;

    /*
     *  \var g
     *  \brief The green value in the range of 0-255
     */
    uint8_t g;

    /*
     *  \var b
     *  \brief The blue value in the range of 0-255
     */
    uint8_t b;

    /*
     *  \var a
     *  \brief The alpha value in the range of 0-255
     */
    uint8_t a;

private:
    NYRA_SERIALIZE()

    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & r;
        archive & g;
        archive & b;
        archive & a;
    }

    friend std::ostream& operator<<(std::ostream& os, const Color& color);
};
}
}

#endif
