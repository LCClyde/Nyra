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
#include <vector>
#include <nyra/cli/Parser.h>
#include <nyra/net/Browser.h>
#include <nyra/img/Algs.h>
#include <nyra/process/Subprocess.h>
#include <nyra/core/File.h>

using namespace nyra;

//===========================================================================//
static const std::string URL = "http://www.arkhamhorrorwiki.com";

//===========================================================================//
std::string parse(size_t start, size_t end,
                  net::Browser& browser)
{
    const std::string urlPrefix = URL + "/wiki/images/";
    const std::string pathname = "gate.png";
    std::string results;

    for (size_t ii = start; ii < end + 1; ++ii)
    {
        const std::string fullUrl =
                urlPrefix + "Gate" + core::str::toString(ii) + ".png";
        browser.download(fullUrl, pathname);
        img::Image image = core::read<img::Image>(pathname);
        image = img::resize(image, image.getSize() * 6);
        image = img::threshold(image, 180);
        const math::Vector2U offset(240, 240);
        const math::Vector2U extents = image.getSize() - (offset * 2);
        image = img::crop(image, offset, extents);
        core::write(image, pathname);
        process::subprocess("/usr/bin/tesseract", {"gate.png", "results"});
        results += core::readFile("results.txt") + "\n";
    }
    return results;
}

//===========================================================================//
int main(int argc, char** argv)
{
    try
    {
        cli::Options opt("Creates the Arkham Horror data files");
        cli::Parser options(opt, argc, argv);

        net::Browser browser(100);

        std::string blue = parse(1, 12, browser);
        std::string green = parse(13, 24, browser);
        std::string red = parse(25, 36, browser);
        std::string yellow = parse(37, 48, browser);

        std::ofstream stream("other_world_encounters.txt");
        stream << "BLUE\n" << blue
               << "\nGREEN\n" << green
               << "\nRED\n" << red
               << "\nYELLLOW\n" << yellow << "\n";

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
