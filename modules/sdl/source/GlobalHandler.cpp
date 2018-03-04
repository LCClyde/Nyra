/*
 * Copyright (c) 2016 Clyde Stanfield
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
#include <nyra/sdl/GlobalHandler.h>
#include <SDL2/SDL.h>

namespace
{
std::string subsystemOstream(uint32_t subsystems, uint32_t target)
{
    if (subsystems & target)
    {
        return "running";
    }
    return "stopped";
}
}

namespace nyra
{
namespace sdl
{
//===========================================================================//
void GlobalHandler::initializeGlobal()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw std::runtime_error("SDL could not initialize. SDL_Error: " +
                std::string(SDL_GetError()));
    }
}

//===========================================================================//
void GlobalHandler::shutdownGlobal()
{
    SDL_Quit();
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os, const GlobalHandler& handler)
{
    const uint32_t subsystems = SDL_WasInit(SDL_INIT_EVERYTHING);
    os << "SDL Global Handler Status:\n"
       << "  Audio: " << subsystemOstream(subsystems, SDL_INIT_AUDIO) << "\n"
       << "  Events: " << subsystemOstream(subsystems, SDL_INIT_EVENTS) << "\n"
       << "  Game Controller: "
       << subsystemOstream(subsystems, SDL_INIT_GAMECONTROLLER) << "\n"
       << "  Haptic: " << subsystemOstream(subsystems, SDL_INIT_HAPTIC) << "\n"
       << "  Joystick: "
       << subsystemOstream(subsystems, SDL_INIT_JOYSTICK) << "\n"
       << "  No Parachute: "
       << subsystemOstream(subsystems, SDL_INIT_NOPARACHUTE) << "\n"
       << "  Timer: " << subsystemOstream(subsystems, SDL_INIT_TIMER) << "\n"
       << "  Video: " << subsystemOstream(subsystems, SDL_INIT_VIDEO);
    return os;
}
}
}
