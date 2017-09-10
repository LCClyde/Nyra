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
#include <nyra/script/Variable.h>
#include <nyra/script/Object.h>
#include <stdint.h>
#include <stdexcept>
#include <limits>

namespace nyra
{
namespace script
{
//===========================================================================//
std::ostream& operator<<(std::ostream& os, const Variable& variable)
{
    os << variable.toString();
    return os;
}

//===========================================================================//
template <>
void Variable::set<int8_t>(const int8_t& value)
{
    setInt(static_cast<int64_t>(value));
}

//===========================================================================//
template <>
void Variable::set<uint8_t>(const uint8_t& value)
{
    setInt(static_cast<int64_t>(value));
}

//===========================================================================//
template <>
void Variable::set<int16_t>(const int16_t& value)
{
    setInt(static_cast<int64_t>(value));
}

//===========================================================================//
template <>
void Variable::set<uint16_t>(const uint16_t& value)
{
    setInt(static_cast<int64_t>(value));
}

//===========================================================================//
template <>
void Variable::set<int32_t>(const int32_t& value)
{
    setInt(static_cast<int64_t>(value));
}

//===========================================================================//
template <>
void Variable::set<uint32_t>(const uint32_t& value)
{
    setInt(static_cast<int64_t>(value));
}

//===========================================================================//
template <>
void Variable::set<int64_t>(const int64_t& value)
{
    setInt(value);
}

//===========================================================================//
template <>
void Variable::set<uint64_t>(const uint64_t& value)
{
    uint64_t compare = static_cast<uint64_t>(
        std::numeric_limits<int64_t>::max());
    if (value > compare)
    {
        throw std::runtime_error(
            "Value is too large to fit into a script variable");
    }
    setInt(static_cast<int64_t>(value));
}

//===========================================================================//
template <>
void Variable::set<std::unique_ptr<Object>>(
        const std::unique_ptr<Object>& value)
{
    setObject(value);
}

//===========================================================================//
template <>
void Variable::set<float>(const float& value)
{
    setFloat(static_cast<double>(value));
}

//===========================================================================//
template <>
void Variable::set<double>(const double& value)
{
    setFloat(value);
}

//===========================================================================//
template <>
void Variable::set<std::string>(const std::string& value)
{
    setString(value);
}

//===========================================================================//
template <>
int8_t Variable::get<int8_t>() const
{
    return static_cast<int8_t>(getInt());
}

//===========================================================================//
template <>
uint8_t Variable::get<uint8_t>() const
{
    return static_cast<uint8_t>(getInt());
}

//===========================================================================//
template <>
int16_t Variable::get<int16_t>() const
{
    return static_cast<int16_t>(getInt());
}

//===========================================================================//
template <>
uint16_t Variable::get<uint16_t>() const
{
    return static_cast<uint16_t>(getInt());
}

//===========================================================================//
template <>
int32_t Variable::get<int32_t>() const
{
    return static_cast<int32_t>(getInt());
}

//===========================================================================//
template <>
uint32_t Variable::get<uint32_t>() const
{
    return static_cast<uint32_t>(getInt());
}

//===========================================================================//
template <>
int64_t Variable::get<int64_t>() const
{
    return getInt();
}

//===========================================================================//
template <>
uint64_t Variable::get<uint64_t>() const
{
    return static_cast<uint64_t>(getInt());
}

//===========================================================================//
template <>
float Variable::get<float>() const
{
    return static_cast<float>(getFloat());
}

//===========================================================================//
template <>
double Variable::get<double>() const
{
    return getFloat();
}

//===========================================================================//
template <>
std::string Variable::get<std::string>() const
{
    return getString();
}

//===========================================================================//
template <>
std::unique_ptr<Object> Variable::get<std::unique_ptr<Object>>() const
{
    return getObject();
}
}
}
