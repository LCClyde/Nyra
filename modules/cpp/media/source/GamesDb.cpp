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
#include <iostream>
#include <unordered_map>
#include <nyra/media/GamesDb.h>
#include <nyra/xml/XML.h>
#include <nyra/core/String.h>

namespace nyra
{
namespace media
{
//===========================================================================//
GamesDb::GamesDb(std::shared_ptr<net::Browser> browser) :
    mBrowser(browser),
    mSite("http://thegamesdb.net/api/")
{
}

//===========================================================================//
std::string GamesDb::getId(const std::string& name,
                           const std::string& platform) const
{
    std::string url = mSite + "GetGame.php";

    std::vector<net::Param> params;
    params.push_back(net::Param("name", name));

    if (!platform.empty())
    {
        params.push_back(net::Param("platform", platform));
    }

    xml::XML results(mBrowser->get(url, params));

    for (size_t ii = 0; ii < results["Data"]["Game"].loopSize(); ++ii)
    {
        if (results["Data"]["Game"][ii]["GameTitle"].get().text == name)
        {
            return results["Data"]["Game"][ii]["id"].get().text;
        }
    }

    return "";
}

//===========================================================================//
void GamesDb::updateGame(const std::string& id,
                         Game::GamesDb& game) const
{
    if (id.empty())
    {
        return;
    }

    std::string url = mSite + "GetGame.php";

    std::vector<net::Param> params;
    params.push_back(net::Param("id", id));

    xml::XML results(mBrowser->get(url, params));

    const std::string baseURL = results["Data"]["baseImgUrl"].get().text;

    game.id = id;

    if (results["Data"]["Game"].has("Rating"))
    {
        game.rating = core::str::toType<double>(
                results["Data"]["Game"]["Rating"].get().text);
    }

    if (results["Data"]["Game"].has("Youtube"))
    {
        game.youtube = results["Data"]["Game"]["Youtube"].get().text;
    }

    if (results["Data"]["Game"].has("Images"))
    {
        const auto& images = results["Data"]["Game"]["Images"];
        if (images.has("fanart"))
        {
            for (size_t ii = 0; ii < images["fanart"].loopSize(); ++ii)
            {
                game.fanArt.push_back(baseURL +
                        images["fanart"][ii]["original"].get().text);
            }
        }

        if (images.has("boxart"))
        {
            for (size_t ii = 0; ii < images["boxart"].loopSize(); ++ii)
            {
                game.boxArt.push_back(baseURL +
                        images["boxart"][ii].get().text);
            }
        }

        if (images.has("banner"))
        {
            for (size_t ii = 0; ii < images["banner"].loopSize(); ++ii)
            {
                game.bannerArt.push_back(baseURL +
                        images["banner"][ii].get().text);
            }
        }
    }
}
}
}
