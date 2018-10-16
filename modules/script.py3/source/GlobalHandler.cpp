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
#pragma push_macro("slots")
#undef slots
#include <Python.h>
#pragma pop_macro("slots")

#include <nyra/script/py3/GlobalHandler.h>
#include <nyra/core/Path.h>
#include <iostream>

namespace nyra
{
namespace script
{
namespace py3
{
//===========================================================================//
void GlobalHandler::initializeGlobal()
{
    Py_Initialize();

    // Add the scripts directory to the PYTHONPATH
    const std::string path = core::path::join(core::DATA_PATH, "scripts");
    const std::string call = "import sys; sys.path.append('" + path + "')\n";
    PyRun_SimpleString(call.c_str());
}

//===========================================================================//
void GlobalHandler::shutdownGlobal()
{
    Py_Finalize();
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os, const GlobalHandler& handler)
{
    if (handler.isInitialized())
    {
        os << "Python 3.x is initialized";
    }
    else
    {
        os << "Python 3.x is not initialized";
    }
    return os;
}
}
}
}
