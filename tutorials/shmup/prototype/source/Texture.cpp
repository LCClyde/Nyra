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
#include <unordered_map>
#include <Texture.h>

namespace
{
//===========================================================================//
struct TextureHandler
{
    TextureHandler(const std::string& filename)
    {
        texture.loadFromFile("data/textures/" + filename);
        image = texture.copyToImage();
    }

    sf::Texture texture;
    sf::Image image;
};

//===========================================================================//
std::unordered_map<std::string, std::unique_ptr<TextureHandler>> textureMap;

//===========================================================================//
TextureHandler* getHandler(const std::string& filename)
{
    auto iter = textureMap.find(filename);

    if (iter == textureMap.end())
    {
        textureMap[filename].reset(new TextureHandler(filename));
        iter = textureMap.find(filename);
    }

    return iter->second.get();
}
}

//===========================================================================//
Texture::Texture(const std::string& filename)
{
    TextureHandler* handler = getHandler(filename);
    mTexture = &handler->texture;
    mImage = &handler->image;
}

//===========================================================================//
bool Texture::isPixel(unsigned int x,
                      unsigned int y) const
{
    if (x > mTexture->getSize().x || y > mTexture->getSize().y)
    {
        return false;
    }

    return mImage->getPixel(x, y).a > 0;
}

