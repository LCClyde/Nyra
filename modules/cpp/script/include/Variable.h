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
#ifndef __NYRA_SCRIPT_VARIABLE_H__
#define __NYRA_SCRIPT_VARIABLE_H__

#include <string>
#include <memory>
#include <vector>

namespace nyra
{
namespace script
{
/*
 *  \class Variable
 *  \brief A class to abstract away setting and getting variables from
 *         a script. The supported types are:
 *             int8_t
 *             uint8_t
 *             int16_t
 *             uint16_t
 *             int32_t
 *             uint32_t
 *             int64_t
 *             uint64_t (values above int64_t throw)
 *             float
 *             double
 *             std::string
 *         There is not a good way to generalize variable serialization.
 *         TODO: Add a serialization option that works on a
 *               std::unique<Variable> and builds up a variable through
 *               a factory.
 */
class Variable
{
public:
    /*
     *  \func Destructor
     *  \brief Necessary for inheritance.
     */
    virtual ~Variable() = default;

    /*
     *  \func set
     *  \brief Sets the variable to a value
     *
     *  \tparam T The variable type.
     *  \param value The value to set.
     */
    template<typename T>
    void set(const T& value);

    /*
     *  \func get
     *  \brief Gets the value from the variable. It is the user's
     *         responsibility to select a reasonable type. Type checking
     *         is not guaranteed. For example a negative int will simply be
     *         static cast if an unsigned int is requested.
     *
     *  \tparam T The variable type.
     *  \return The value of the variable evaluated with the desired type.
     */
    template<typename T>
    T get() const;

private:
    friend std::ostream& operator<<(std::ostream& os, const Variable& variable);

    virtual void setInt(int64_t value) = 0;

    virtual void setFloat(double value) = 0;

    virtual void setString(const std::string& value) = 0;

    virtual int64_t getInt() const = 0;

    virtual double getFloat() const = 0;

    virtual std::string getString() const = 0;

    virtual std::string toString() const = 0;
};

typedef std::unique_ptr<Variable> VariablePtr;
typedef std::initializer_list<Variable*> VariableList;
}
}

#endif
