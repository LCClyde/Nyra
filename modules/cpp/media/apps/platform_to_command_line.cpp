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
        if (argc < 5)
        {
            std::cout << "Usage: " << argv[0]
                      << " <LUT> <platform> <binary> <args>\n";
            return 1;
        }

        media::PlatformToBinary p2b;
        if (core::path::exists(argv[1]))
        {
            core::readArchive<media::PlatformToBinary>(argv[1], p2b, core::XML);
        }
        else
        {
            std::cout << argv[1] << " does not exist. It will be created.\n";
        }

        media::GameCommandLine cmd;
        cmd.binary = argv[3];
        cmd.args.push_back(argv[4]);
        p2b[argv[2]] = cmd;

        core::writeArchive(p2b, argv[1], core::XML);
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

