/*
 * Copyright (c) 2016 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
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
#ifndef __NYRA_SCRIPT_PY3_VARIABLE_H__
#define __NYRA_SCRIPT_PY3_VARIABLE_H__

#include <nyra/script/Variable.h>
#include <nyra/pattern/GlobalDependency.h>
#include <nyra/script/py3/GlobalHandler.h>
#include <nyra/script/py3/AutoPy.h>

namespace nyra
{
namespace script
{
namespace py3
{
/*
 *  \class Variable
 *  \brief Class that represents a variable that can translate to
 *         Python 3.x
 */
class Variable : public nyra::script::Variable
{
private:
    void setInt(int64_t value) override;

    void setFloat(double value) override;

    void setString(const std::string& value) override;

    int64_t getInt() const override;

    double getFloat() const override;

    std::string getString() const override;

    std::string toString() const override;

    AutoPy mData;
};
}
}
}

#endif
