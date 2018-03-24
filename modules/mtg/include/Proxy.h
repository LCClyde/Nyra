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
#ifndef __NYRA_MTG_PROXY_H__
#define __NYRA_MTG_PROXY_H__

#include <nyra/mtg/Card.h>
#include <nyra/img/Image.h>

namespace nyra
{
namespace mtg
{
class Proxy
{
public:
    img::Image create(const Card& card,
                      const std::string& artPathname);

private:
    void getColor();

    img::Image createBorder() const;

    img::Image createBackground() const;

    img::Image createDesign() const;

    img::Image createText() const;

    img::Image createTextBoxes() const;

    img::Image createSingleTextBox(const std::string& name,
                                   const img::Color& bgColor) const;

    img::Image createArt() const;

    img::Image createCasingCost() const;

    img::Image drawTextBoxText(math::Vector2U& size) const;

    Card mCard;
    std::string mColor;
    std::string mArtPathname;
    bool mFullArt;

};
}
}

#endif
