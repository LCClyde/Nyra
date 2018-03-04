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
#include <nyra/arkham/Expansion.h>
#include <nyra/core/String.h>

namespace nyra
{
namespace arkham
{
//===========================================================================//
Expansion stringToExpansion(const std::string exp)
{
    if (exp == "Core" || exp.empty())
    {
        return CORE;
    }
    else if (exp == "Kingsport Horror")
    {
        return KINGSPORT;
    }
    else if (exp == "Dunwich Horror")
    {
        return DUNWICH;
    }
    else if (exp == "Innsmouth Horror")
    {
        return INNSMOUTH;
    }
    else if (exp == "The Lurker at the Threshold")
    {
        return LURKER;
    }
    else if (exp == "Curse of the Dark Pharaoh")
    {
        return PHARAOH;
    }
    else if (exp == "Curse of the Dark Pharaoh (Revised Edition)")
    {
        return PHARAOH_REVISED;
    }
    else if (exp == "The Black Goat of the Woods")
    {
        return BLACK_GOAT;
    }
    else if (exp == "The King in Yellow")
    {
        return KING_YELLOW;
    }
    else if (core::str::startsWith(exp, "Miskatonic Horror"))
    {
        return MISKATONIC;
    }
    throw std::runtime_error("Invalid expansion " + exp);
}

//===========================================================================//
std::string expansionToString(Expansion exp)
{
    switch (exp)
    {
    case CORE:
        return "Core";
    case KINGSPORT:
        return "Kingsport Horror";
    case DUNWICH:
        return "Dunwich Horror";
    case INNSMOUTH:
        return "Innsmouth Horror";
    case LURKER:
        return "The Lurker at the Threshold";
    case PHARAOH:
        return "Curse of the Dark Pharaoh";
    case PHARAOH_REVISED:
        return "Curse of the Dark Pharaoh (Revised Edition)";
    case BLACK_GOAT:
        return "The Black Goat of the Woods";
    case KING_YELLOW:
        return "The King in Yellow";
    case MISKATONIC:
        return "Miskatonic Horror";
    default:
        throw std::runtime_error("Invalid expansion");
    }
}
}
}
