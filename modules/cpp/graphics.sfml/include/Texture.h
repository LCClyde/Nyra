/*
 * Copyright (c) 2016 Clyde Stanfield
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
#ifndef __NYRA_GRAPHICS_SFML_TEXTURE_H__
#define __NYRA_GRAPHICS_SFML_TEXTURE_H__

#include <SFML/Graphics.hpp>

namespace nyra
{
namespace graphics
{
namespace sfml
{
/*
 *  \class Texture
 *  \brief Wraps an SFML texture so it can be constructed with a pathname.
 */
class Texture
{
public:
    /*
     *  \func Constructor
     *  \brief Creates an SFML texture.
     */
    Texture(const std::string& pathname);

    /*
     *  \func get
     *  \brief  Gets the SFML texture.
     *
     *  \return The SFML texture.
     */
    const sf::Texture& get() const
    {
        return mTexture;
    }

private:
    sf::Texture mTexture;
};
}
}
}

#endif
