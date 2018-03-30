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
#include <unordered_map>
#include <nyra/mtg/Proxy.h>
#include <nyra/core/Path.h>
#include <nyra/core/String.h>
#include <nyra/img/Algs.h>
#include <nyra/img/Draw.h>

namespace
{
static const nyra::math::Vector2U BLEED_AREA(822, 1122);
static const size_t TITLE_BOX_Y = 178;
static const size_t TITLE_TEXT_Y = TITLE_BOX_Y + 5;
static const size_t ART_FRAME_Y = TITLE_BOX_Y + 172;
static const size_t ART_Y = ART_FRAME_Y + 78;
static const size_t TYPE_BOX_Y = ART_FRAME_Y + 300;
static const size_t TYPE_TEXT_Y = TYPE_BOX_Y + 2;
static const size_t TEXT_BOX_Y = TYPE_BOX_Y + 190;
static const size_t TEXT_TEXT_Y = TEXT_BOX_Y;
static const size_t MANA_Y = TITLE_TEXT_Y - 102;
static const nyra::math::Vector2U PT_BOX (0, TEXT_BOX_Y + 165);
static const nyra::math::Vector2U PT_TEXT(PT_BOX.x, PT_BOX.y);
static const std::unordered_map<std::string, nyra::img::Color> COLOR_MAP =
{
    {"white", nyra::img::Color(255, 140, 0)},
    {"blue", nyra::img::Color(3, 16, 79)},
    {"black", nyra::img::Color(192, 192, 192)},
    {"red", nyra::img::Color(230, 167, 31)},
    {"green", nyra::img::Color(222, 184, 135)},
    {"gold", nyra::img::Color(15, 15, 15)},
    {"artifact", nyra::img::Color(31, 31, 31)},
    {"land", nyra::img::Color(56, 37, 18)}
};
static const std::unordered_map<std::string, nyra::img::Color> BOX_COLOR =
{
    {"white", nyra::img::Color(255, 255, 255)},
    {"blue", nyra::img::Color(173,216,230)},
    {"black", nyra::img::Color(128, 128, 128)},
    {"red", nyra::img::Color(255, 153, 153)},
    {"green", nyra::img::Color(204, 255, 204)},
    {"gold", nyra::img::Color(250, 250, 210)},
    {"artifact", nyra::img::Color(229, 220, 200)},
    {"land", nyra::img::Color(225, 193, 163)}
};

//===========================================================================//
void getColorID(nyra::mtg::Mana testCost,
                const std::string& testColor,
                nyra::mtg::Mana cost,
                std::string& name)
{
    if (cost == testCost)
    {
        if (name.empty())
        {
            name = testColor;
        }
        else if (name != testColor)
        {
            name = "gold";
        }
    }
}

//===========================================================================//
nyra::math::Vector2U center(const nyra::math::Vector2U& size,
                            const nyra::math::Vector2U& targetSize)
{
    nyra::math::Vector2U result = targetSize / 2;
    result -= size / 2;
    return result;
}

//===========================================================================//
nyra::math::Vector2U center(const nyra::math::Vector2U& size)
{
    return center(size, BLEED_AREA);
}

//===========================================================================//
nyra::img::Color overlay(const nyra::img::Color& a,
                         const nyra::img::Color& b)
{
    nyra::img::Color color =
            nyra::math::linearInterpolate(a, b, b.a / 255.0);
    color.a = std::max(a.a, b.a);
    return color;
}

//===========================================================================//
void overlay(nyra::img::Image& a,
             const nyra::img::Image& b,
             const nyra::math::Vector2U& offset = nyra::math::Vector2U(),
             const nyra::math::Vector2U& bOffset = nyra::math::Vector2U())
{
    const nyra::math::Vector2U aSize = a.getSize();
    const nyra::math::Vector2U bSize = b.getSize();
    nyra::img::Image result(aSize);


    if (offset.x > aSize.x || offset.y > aSize.y)
    {
        std::cout  << "SOMETHING REALLY BAD PROBABLY HAPPEND\n";
        return;
    }

    nyra::math::Vector2U loopSize(std::min(bSize.x - bOffset.x, aSize.x - offset.x),
                                  std::min(bSize.y - bOffset.y, aSize.y - offset.y));

    for (size_t row = 0; row < loopSize.y; ++row)
    {
        for (size_t col = 0; col < loopSize.x; ++col)
        {
            a(offset.x + col, offset.y + row) =
                    overlay(a(offset.x + col, offset.y + row),
                               b(col + bOffset.x, row + bOffset.y));
        }
    }
}

//===========================================================================//
bool isCreature(const nyra::mtg::Card& card)
{
    for (auto type : card.types)
    {
        if (type == nyra::mtg::CREATURE)
        {
            return true;
        }
    }
    return false;
}

//===========================================================================//
bool isSymbol(const std::string& text)
{
    if (text.size() != 1)
    {
        return false;
    }

    static const std::vector<char> symbols =
            {'W', 'U', 'B', 'R', 'G', 'C', 'T', 'X'};
    return (std::find(symbols.begin(), symbols.end(), text[0]) != symbols.end() ||
            std::isdigit(text[0]));
}

//===========================================================================//
nyra::math::Vector2U drawTextOrSymbol(const std::string& text,
                                      const nyra::img::Font& font,
                                      const nyra::math::Vector2U& inOffset,
                                      nyra::img::Image& image)
{

    if (isSymbol(text))
    {
        const std::string pathname = nyra::core::path::join(
                nyra::core::DATA_PATH, "textures/symbol_" + text + "_small.png");
        nyra::img::Image symbol = nyra::core::read<nyra::img::Image>(pathname);
        symbol = nyra::img::resize(symbol, nyra::math::Vector2U(35, 35));

        nyra::math::Vector2U symbolOffset(inOffset);

        // Check if we go off the end of the line
        if (symbolOffset.x + symbol.getSize().x > image.getSize().x)
        {
            nyra::img::Image tempImage(nyra::math::Vector2U(64, 64));
            nyra::img::Font tempFont(font);
            tempFont.returnNextLine = true;
            nyra::math::Vector2U textOffset =
                    nyra::img::draw::text(
                            "a", nyra::math::Vector2U(), tempFont, tempImage);
            symbolOffset.y += textOffset.y;
            symbolOffset.x = 0;
        }

        overlay(image, symbol, symbolOffset);

        return nyra::math::Vector2U(
                symbolOffset.x + symbol.getSize().x, symbolOffset.y);
    }
    else
    {
        nyra::math::Vector2U textOffset(inOffset);

        // We always want this set to zero. The font controls the x offset
        // of the first line.
        textOffset.x = 0;

        nyra::math::Vector2U offset =
                nyra::img::draw::text(text, textOffset, font, image);
        return offset;
    }
}

//===========================================================================//
std::vector<std::string> splitSymbols(const std::string& text)
{
    std::vector<std::string> split = nyra::core::str::split(text, "{");
    std::vector<std::string> results;

    for (const std::string& res : split)
    {
        const auto noSymbols = nyra::core::str::split(res, "}");
        results.insert(results.end(), noSymbols.begin(), noSymbols.end());
    }

    return results;
}
}

namespace nyra
{
namespace mtg
{
//===========================================================================//
img::Image Proxy::create(const Card& card,
                         const std::string& artPathname)
{
    mCard = card;
    getColor();
    mArtPathname = artPathname;
    mFullArt = card.rarity == mtg::BASIC_LAND;

    img::Image result = createBackground();

    img::Image art = createArt();
    math::Vector2U offset = center(art.getSize());

    // Full art stays in the center
    if (!mFullArt)
    {
        offset.y = ART_Y - art.getSize().y / 2;
    }
    overlay(result, art, offset);

    img::Image design = createDesign();
    overlay(result, design, center(design.getSize()));
    overlay(result, createTextBoxes());

    if (!mFullArt)
    {
        overlay(result, createCasingCost());
    }

    overlay(result, createText());
    overlay(result, createBorder());
    return result;
}

//===========================================================================//
img::Image Proxy::createBorder() const
{
    const std::string pathname = core::path::join(
            core::DATA_PATH, "textures/border.png");
    return core::read<img::Image>(pathname);
}

//===========================================================================//
void Proxy::getColor()
{
    const auto& cost = mCard.cost;
    std::string color;

    for (auto t : mCard.types)
    {
        if (t == ARTIFACT)
        {
            color = "artifact";
            break;
        }
        else if (t == LAND)
        {
            color = "land";
            break;
        }
    }

    if (color.empty())
    {
        for (auto c : cost)
        {
            getColorID(WHITE, "white", c, color);
            getColorID(BLUE, "blue", c, color);
            getColorID(BLACK, "black", c, color);
            getColorID(RED, "red", c, color);
            getColorID(GREEN, "green", c, color);
        }
    }

    if (mCard.rarity == mtg::BASIC_LAND)
    {
        if (mCard.name == "Plains")
        {
            color = "white";
        }
        else if (mCard.name == "Island")
        {
            color = "blue";
        }
        else if (mCard.name == "Swamp")
        {
            color = "black";
        }
        else if (mCard.name == "Mountain")
        {
            color = "red";
        }
        else if (mCard.name == "Forest")
        {
            color = "green";
        }
    }

    if (color.empty())
    {
        throw std::runtime_error(
                "Could not determine background for: " + mCard.name);
    }

    mColor = color;
}

//===========================================================================//
img::Image Proxy::createBackground() const
{

    const std::string filename = "proxy_" + mColor + "_background.png";
    const std::string pathname = core::path::join(
            core::DATA_PATH, "textures/" + filename);
    img::Image backgroundImg = core::read<img::Image>(pathname);

    if (backgroundImg.getSize() != BLEED_AREA)
    {
        throw std::runtime_error(
                pathname + " is not sized correctly. It must be: " +
                core::str::toString(BLEED_AREA.x) + " " +
                core::str::toString(BLEED_AREA.y) + " pixels.");
    }
    return backgroundImg;
}

//===========================================================================//
img::Image Proxy::createDesign() const
{
    img::Image border = core::read<img::Image>(
            core::path::join(core::DATA_PATH, "textures/fancy_border.png"));

    const std::string frameFilename = mFullArt ?
            "full_art_frame.png" : "art_frame.png";
    img::Image frame = core::read<img::Image>(
            core::path::join(core::DATA_PATH, "textures/" + frameFilename));
    math::Vector2U offset = center(frame.getSize(), border.getSize());

    if (!mFullArt)
    {
        offset.y = ART_FRAME_Y - frame.getSize().y / 2;
    }
    overlay(border, frame, offset);
    border = img::invert(border);
    border *= COLOR_MAP.at(mColor);
    return border;
}

//===========================================================================//
img::Image Proxy::createText() const
{
    // Base alpha image
    img::Image result(BLEED_AREA);
    result = img::Color(0, 0, 0, 0);

    // Card title
    img::Image image(math::Vector2U(440, 200));

    img::Font font;
    font.name = "Carrington";
    font.size = 50;
    font.color = img::Color::BLACK;
    font.bold = false;
    font.italic = false;
    math::Vector2U size;

    do
    {
        image = img::Color::ALPHA;
        size = img::draw::text(mCard.name, math::Vector2U(), font, image);
        font.size -= 1;
    }
    while (size.x > image.getSize().x);

    math::Vector2U offset = center(size);
    offset.y = TITLE_TEXT_Y - size.y / 2;
    overlay(result, image, offset);

    if (!mFullArt)
    {
        // Card type
        image = img::Image(math::Vector2U(300, 200));

        font.name = "Della Respira";
        font.size = 30;
        std::string type;
        const std::string superTypes = supertypeToString(mCard.supertypes);
        const std::string types = typeToString(mCard.types);

        type += superTypes;
        if (!type.empty())
        {
            type += " ";
        }
        type += types;

        if (!mCard.subtypes.empty())
        {
            type += " —";
            for (size_t ii = 0; ii < mCard.subtypes.size(); ++ii)
            {
                type += " " + mCard.subtypes[ii];
            }
        }

        do
        {
            image = img::Color::ALPHA;
            size = img::draw::text(type, math::Vector2U(), font, image);
            font.size -= 1;
        }
        while (size.x > image.getSize().x);

        offset = center(size);
        offset.y = TYPE_TEXT_Y - size.y / 2;
        overlay(result, image, offset);

        // Card text
        math::Vector2U textSize;
        image = drawTextBoxText(textSize);
        offset.x = 175;
        offset.y = TEXT_TEXT_Y - (textSize.y / 2);
        overlay(result, image, offset);

        // Power / Toughness
        if (isCreature(mCard))
        {
            image = img::Image(math::Vector2U(200, 200));
            image = img::Color(0, 0, 0, 0);
            font.size = 30;

            font.size = 36;
            const std::string power =
                    mCard.power == Card::SPECIAL_VALUE ?
                            "*" : core::str::toString(mCard.power);
            const std::string toughness =
                    mCard.toughness == Card::SPECIAL_VALUE ?
                            "*" : core::str::toString(mCard.toughness);
            const std::string text = power + "/" + toughness;
            size = img::draw::text(text, math::Vector2U(), font, image);
            offset = center(size);
            offset.y = PT_TEXT.y - size.y / 2;
            overlay(result, image, offset);
        }
    }

    return result;
}

//===========================================================================//
img::Image Proxy::drawTextBoxText(math::Vector2U& size) const
{
    size.x = 0;
    size.y = 0;

    img::Font font;
    font.name = "Della Respira";
    font.color = img::Color::BLACK;
    font.size = 30;

    // We have an extraTextY offset here to allow some extra room to
    // add symbols to the first line if necessary.
    const size_t extraTextY = 20;
    img::Image image(math::Vector2U(470, 275 + extraTextY));

    const std::vector<std::string> lines = core::str::split(mCard.text, "\n");
    math::Vector2U textOffset;
    font.maxWidth = image.getSize().x;
    const size_t spacing = 8;

    do
    {
        image = img::Color::ALPHA;
        textOffset = math::Vector2U(0, extraTextY - 1);
        for (size_t ii = 0; ii < lines.size(); ++ii)
        {
            const std::vector<std::string> textAndSymbols =
                    splitSymbols(lines[ii]);
            for (size_t jj = 0; jj < textAndSymbols.size(); ++jj)
            {
                font.returnNextLine = (jj == textAndSymbols.size() - 1);
                textOffset = drawTextOrSymbol(
                        textAndSymbols[jj], font, textOffset, image);
                font.xOffset = textOffset.x;
            }
            font.xOffset = 0;
            textOffset.y += spacing;
        }

        font.size -= 1;
    } while (textOffset.y >= image.getSize().y);

    // This is wasteful, but it keeps the return from here simple.
    img::Image realImage(math::Vector2U(image.getSize().x,
                                        image.getSize().y - extraTextY));
    realImage = img::Color::ALPHA;
    overlay(realImage, image,
            math::Vector2U(),
            math::Vector2U(0, extraTextY - 1));

    size = textOffset;
    size.y -= (extraTextY + spacing);
    return realImage;
}

//===========================================================================//
img::Image Proxy::createTextBoxes() const
{
    img::Image result(BLEED_AREA);
    result = img::Color::ALPHA;
    img::Image box;
    const img::Color boxColor = BOX_COLOR.at(mColor);

    box = createSingleTextBox("name_box", boxColor);
    math::Vector2U offset = center(box.getSize());
    offset.y = TITLE_BOX_Y - box.getSize().y / 2;
    overlay(result, box, offset);

    if (!mFullArt)
    {
        box = createSingleTextBox("text_box", boxColor);
        offset = center(box.getSize());
        offset.y = TEXT_BOX_Y - box.getSize().y / 2;
        overlay(result, box, offset);

        box = createSingleTextBox("type_box", boxColor);
        offset = center(box.getSize());
        offset.y = TYPE_BOX_Y - box.getSize().y / 2;
        overlay(result, box, offset);

        if (isCreature(mCard))
        {
            box = createSingleTextBox("pt_box", boxColor);
            offset = center(box.getSize());
            offset.y = PT_BOX.y - box.getSize().y / 2;
            overlay(result, box, offset);
        }
    }

    return result;
}

//===========================================================================//
img::Image Proxy::createSingleTextBox(const std::string& name,
                                      const img::Color& bgColor) const
{
    const img::Color trueColor(COLOR_MAP.at(mColor));
    const img::Color invertColor(255 - trueColor.r,
                                 255 - trueColor.g,
                                 255 - trueColor.b);

    img::Image image = core::read<img::Image>(
            core::path::join(core::DATA_PATH, "textures/" + name + ".png"));
    image = img::invert(image);
    image *= invertColor;
    image = img::invert(image);

    img::Image bg = core::read<img::Image>(
            core::path::join(core::DATA_PATH, "textures/" + name + "_bg.png"));
    bg *= bgColor;

    // The backgrounds may be slightly smaller so we need to overlay
    // everything into a new image
    img::Image final(math::Vector2U(
            std::max(image.getSize().x, bg.getSize().x),
            std::max(image.getSize().y, bg.getSize().y)));
    final = img::Color::ALPHA;

    math::Vector2U offset = center(bg.getSize(), final.getSize());
    overlay(final, bg, offset);
    offset = center(image.getSize(), final.getSize());
    overlay(final, image, offset);
    return final;
}

//===========================================================================//
img::Image Proxy::createArt() const
{
    img::Image art = core::read<img::Image>(mArtPathname);

    const std::string maskFilename = mFullArt ?
            "full_art_mask.png" : "art_mask.png";
    img::Image mask = core::read<img::Image>(
            core::path::join(core::DATA_PATH,
                             "textures/" + maskFilename));

    for (size_t ii = 0; ii < art.getSize().product(); ++ii)
    {
        art(ii).a = mask(ii).r;
    }
    return art;
}

//===========================================================================//
img::Image Proxy::createCasingCost() const
{
    img::Image image(math::Vector2U(500, 128));
    image = img::Color::ALPHA;

    const std::string cost = manaToString(mCard.cost);
    const std::vector<std::string> symbols = core::str::split(cost, "{");
    size_t offset = 0;
    for (std::string symbol : symbols)
    {
        if (symbol.empty())
        {
            continue;
        }

        const std::string filename = "textures/symbol_" +
                std::string(1, symbol[0]) + ".png";
        const std::string pathname =
                core::path::join(core::DATA_PATH, filename);
        img::Image symbolImg = core::read<img::Image>(pathname);
        overlay(image, symbolImg, math::Vector2U(offset, 0));
        offset += symbolImg.getSize().x;
    }

    img::Image final(BLEED_AREA);
    final = img::Color::ALPHA;
    const math::Vector2U centerOffset = center(math::Vector2U(offset, 0));
    centerOffset.y = MANA_Y;
    overlay(final, image, centerOffset);
    return final;
}
}
}


