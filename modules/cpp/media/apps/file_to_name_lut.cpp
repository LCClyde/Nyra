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
#include <string>
#include <iostream>
#include <exception>
#include <nyra/core/Archive.h>
#include <nyra/core/Path.h>
#include <nyra/media/Types.h>

using namespace nyra;

int main(int argc, char** argv)
{
    try
    {
        if (argc < 4)
        {
            std::cout << "Usage: " << argv[0]
                      << " <LUT> <Filename> <Game Name>\n";
            return 1;
        }

        media::FileToName lut;
        if (core::path::exists(argv[1]))
        {
            core::read<media::FileToName>(argv[1], lut, core::XML);
        }
        else
        {
            std::cout << argv[1] << " does not exist. It will be created.\n";
        }

        const std::vector<std::string> splitPath = core::path::split(argv[2]);
        const std::string& filename = splitPath.back();

        lut[filename] = argv[3];

        core::write(lut, argv[1], core::XML);
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

