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
#include <nyra/core/Time.h>
#include <nyra/map/Parchment.h>
#include <nyra/map/LandMask.h>
#include <nyra/cli/Parser.h>

using namespace nyra;


int main(int argc, char** argv)
{
    try
    {
        cli::Options opt("Creates random 2D rpg town map");
        cli::Parser options(opt, argc, argv);


        size_t seed = core::epoch();
        const math::Vector2U size = map::DEFAULT_SIZE;
        const img::Image parchment(map::Parchment(seed++).getImage(size));

        core::write(parchment, "parchment.png");

        const img::Image landMask(map::LandMask(0.33, seed++).getImage(size));
        img::Image landColor(size);
        for (size_t ii = 0; ii < size.product(); ++ii)
        {
            landColor(ii) = img::Color(64, 164, 223);
        }
        core::write(landMask * landColor, "water.png");
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
