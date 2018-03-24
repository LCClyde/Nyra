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
#include <iostream>
#include <exception>
#include <nyra/cli/Parser.h>
#include <nyra/mtg/Proxy.h>
#include <nyra/mtg/Set.h>
#include <nyra/core/Path.h>
#include <nyra/core/File.h>

using namespace nyra;

namespace
{
void cleanPathname(std::string& pathname)
{

    const std::string badChars = ":'-";
    for (size_t ii = 0; ii < badChars.size(); ++ii)
    {
        pathname = core::str::findAndReplace(
                pathname, std::string(1, badChars[ii]), "");
    }
}
}

int main(int argc, char** argv)
{
    try
    {
        cli::Options opt("Creates a MTG Proxy card");
        opt.add("input", "The input text file").setPositional();
        cli::Parser options(opt, argc, argv);

        const std::string inputPathname = options.get("input");
        const std::string deckName =  core::path::getBase(inputPathname);
        const std::string input = core::readFile(inputPathname);
        const std::vector<std::string> cardNames =
                core::str::split(input, "\n");

        const std::string setPathname = core::path::join(
                core::DATA_PATH, "docs/mtg_");
        const std::string outDir = "proxies/" + deckName;
        std::cout << "Output directory: " << outDir << "\n";
        if (core::path::exists(outDir))
        {
            std::cout << "Deleting previous content at: " << outDir << "\n";
            core::path::removeAll(outDir);
        }
        std::cout << "Creating directory: " << outDir << "\n";
        core::path::makeDirectory(outDir);

        std::cout << "Loading 5th Edition\n";
        mtg::Set set(setPathname + "5ed.json");
        std::cout << "Loading Mirage\n";
        set.addSet(mtg::Set(setPathname + "mir.json"));
        std::cout << "Loading Visions\n";
        set.addSet(mtg::Set(setPathname + "vis.json"));
        std::cout << "Loading Weatherlight\n";
        set.addSet(mtg::Set(setPathname + "wth.json"));
        std::cout << "Loading Tempest\n";
        set.addSet(mtg::Set(setPathname + "tmp.json"));
        std::cout << "Loading Stronghold\n";
        set.addSet(mtg::Set(setPathname + "sth.json"));
        std::cout << "Loading Exodus\n";
        set.addSet(mtg::Set(setPathname + "exo.json"));

        const auto& cards = set.getAllCards();
        std::cout << "Number of cards loaded: " << cards.size() << "\n\n";

        mtg::Proxy proxy;
        size_t totalCards = 0;

        for (const std::string& line : cardNames)
        {
            if (line.empty() || line[0] == '#')
            {
                continue;
            }

            const std::vector<std::string> parts = core::str::split(line, " ");
            const size_t num = core::str::toType<size_t>(parts[0]);
            std::string name;
            for (size_t ii = 1; ii < parts.size(); ++ii)
            {
                name += parts[ii] + " ";
            }
            name = name.substr(0, name.size() - 1);

            mtg::Card card;
            for (const auto& c : cards)
            {
                if (c.name == name)
                {
                    card = c;
                    std::cout << "=========================================\n";
                    std::cout << "Found: " << card << "\n";
                    std::cout << "=========================================\n";
                    break;
                }
            }

            if (card.name.empty())
            {
                throw std::runtime_error("Could not find card: " + name);
            }

            std::string art = "proxies/art/" + name + ".png";
            cleanPathname(art);
            std::cout << "Creating proxy for: " << name << "\n";
            img::Image image = proxy.create(card, art);

            for (size_t ii = 0; ii < num; ++ii)
            {
                ++totalCards;
                std::string numName = totalCards < 10 ? "0" : "";
                numName += core::str::toString(totalCards) + " ";
                std::string output = outDir + "/" + numName + name + ".png";
                cleanPathname(output);
                std::cout << "Saving: " << output << "\n";
                core::write(image, output);
            }
        }
    }
    catch (const std::exception& ex)
    {
        std::cout << "STD Exception: " << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown Exception: System Error!" << std::endl;
    }

    return 0;
}
