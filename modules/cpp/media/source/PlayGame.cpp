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
#include <nyra/media/PlayGame.h>
#include <nyra/core/String.h>
#include <nyra/core/Path.h>

namespace
{
//===========================================================================//
std::string parseCommand(std::string command,
                         const std::string& pathname)
{
    command = nyra::core::str::findAndReplace(
            command, "{GAME}", pathname);
    command = nyra::core::str::findAndReplace(
            command, "{DATA_PATH}", nyra::core::DATA_PATH);
    command = nyra::core::str::findAndReplace(
            command, "{INSTALL_PATH}", nyra::core::INSTALL_PATH);
    return command;
}

//===========================================================================//
std::vector<std::string> parseArguments(std::vector<std::string> args,
                                        const std::string& pathname)
{
    for (size_t ii = 0; ii < args.size(); ++ii)
    {
        args[ii] = parseCommand(args[ii], pathname);
    }
    return args;
}
}

namespace nyra
{
namespace media
{
//===========================================================================//
PlayGame::PlayGame(const GameCommandLine& commandLine,
                   const std::string& pathname,
                   graphics::RenderTarget& target,
                   input::Keyboard& keyboard) :
    Screen(target, keyboard),
    mProcess(parseCommand(commandLine.binary, pathname),
             parseArguments(commandLine.args, pathname))
{
}

//===========================================================================//
void PlayGame::update(double delta)
{
}

//===========================================================================//
void PlayGame::render()
{
}
}
}
