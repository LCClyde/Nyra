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
#include <nyra/mtg/Proxy.h>
#include <nyra/core/Path.h>
#include <nyra/core/String.h>

namespace
{
static const nyra::math::Vector2U SAFE_AREA(678, 978);
static const nyra::math::Vector2U CUT_AREA(750, 1050);
static const nyra::math::Vector2U BLEED_AREA(822, 1122);
}

namespace nyra
{
namespace mtg
{
//===========================================================================//
Proxy::Proxy()
{
}

//===========================================================================//
img::Image Proxy::create(const Card& card) const
{
    img::Image result = createBackground(card);
    return result;
}

//===========================================================================//
img::Image Proxy::createBackground(const Card& card) const
{
    const auto& cost = card.cost;
    std::string background;

    for (auto c : cost)
    {
        if (c == RED)
        {
            background = "red";
        }
    }

    if (background.empty())
    {
        throw std::runtime_error(
                "Could not determine background for: " + card.name);
    }

    const std::string filename = "proxy_" + background + "_background.png";
    const std::string pathname = core::path::join(
            core::DATA_PATH, "textures/" + filename);
    const img::Image backgroundImg = core::read<img::Image>(pathname);

    if (backgroundImg.getSize() != BLEED_AREA)
    {
        throw std::runtime_error(
                pathname + " is not sized correctly. It must be: " +
                core::str::toString(BLEED_AREA.x) + " " +
                core::str::toString(BLEED_AREA.y) + " pixels.");
    }
    return backgroundImg;
}
}
}


