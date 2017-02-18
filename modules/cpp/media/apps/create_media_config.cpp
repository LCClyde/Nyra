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
#include <exception>
#include <nyra/json/JSON.h>
#include <nyra/cli/Parser.h>
#include <nyra/core/Path.h>

using namespace nyra;

int main(int argc, char** argv)
{
    try
    {
        cli::Options opt("Creates the Media Center config file. Parameters "
                         "that are not provided will remain unchanged");
        opt.add("input", "Specify the input config file.").setDefault("config.json");
        opt.add("output", "Specify the output config file. If this is "
                "not set, the config file will overwrite the input.");
        opt.add("data", "Specify the location of the data directory");
        opt.add("win-size", "Specify the window size as WWWXHHH");
        cli::Parser options(opt, argc, argv);

        const std::string inputPathname = options.get("input");
        const std::string outputPathname =
                options.isSet("output") ? options.get("output") : inputPathname;

        json::JSON config;

        if (core::path::exists(inputPathname))
        {
            core::read<json::JSON>(inputPathname, config);
        }

        if (options.isSet("data"))
        {
            config["data_path"] = new std::string(options.get("data"));
        }

        if (options.isSet("win-size"))
        {
            const std::vector<std::string> winSize =
                    core::str::split(options.get("win-size"), "X");

            if (winSize.size() != 2)
            {
                throw std::runtime_error("Invalid window size: " +
                                         options.get("win-size"));
            }
            config["window_width"] = new std::string(winSize[0]);
            config["window_height"] = new std::string(winSize[1]);
        }

        core::write<json::JSON>(config, outputPathname);
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
