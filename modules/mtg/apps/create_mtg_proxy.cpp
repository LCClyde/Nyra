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

using namespace nyra;

int main(int argc, char** argv)
{
    try
    {
        cli::Options opt("Creates a MTG Proxy card");
        opt.add("name", "The card name").setPositional();
        opt.add("output", "The output pathname").setPositional();
        cli::Parser options(opt, argc, argv);

        const std::string name = options.get("name");
        const std::string output = options.get("output");
        const std::string setPathname = core::path::join(core::DATA_PATH, "docs/mtg_");

        mtg::Set set(setPathname + "5ed.json");
        set.addSet(mtg::Set(setPathname + "mir.json"));
        set.addSet(mtg::Set(setPathname + "vis.json"));
        set.addSet(mtg::Set(setPathname + "wth.json"));
        set.addSet(mtg::Set(setPathname + "tmp.json"));
        set.addSet(mtg::Set(setPathname + "sth.json"));
        set.addSet(mtg::Set(setPathname + "exo.json"));

        const auto& cards = set.getAllCards();
        std::cout << "Number of cards loaded: " << cards.size() << "\n";

        mtg::Card card;
        for (const auto& c : cards)
        {
            if (c.name == name)
            {
                card = c;
                std::cout << "Found: " << card << "\n";
                break;
            }
        }

        if (card.name.empty())
        {
            throw std::runtime_error("Could not find card: " + name);
        }

        mtg::Proxy proxy;
        core::write(proxy.create(card), output);
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
