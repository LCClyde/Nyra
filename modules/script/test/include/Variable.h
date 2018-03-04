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
#include <nyra/test/Archive.h>
#include <nyra/test/Stdout.h>
#include <stdint.h>

namespace nyra
{
namespace test
{
/*
 *  \class Variable
 *  \brief A class for testing common functionality in script variables.
 *
 *  \tparam T The variable type to test.
 */
template<typename T>
class Variable : public ::testing::Test
{
public:
    /*
     *  \func Constructor
     *  \brief Sets expected values to test against.
     */
    Variable() :
        expectedInt8(-125),
        expectedUInt8(125),
        expectedInt16(-2125),
        expectedUInt16(2125),
        expectedInt32(-20012500),
        expectedUInt32(20012500),
        expectedInt64(-200125000000),
        expectedUInt64(200125000000),
        expectedFloat(3.14f),
        expectedDouble(1.61803398875),
        expectedString("hello world"),
        expectedIntOut("-20012500"),
        expectedFloatOut("1.6180"),
        expectedStringOut("hello world")
    {
    }

    /*
     *  \func int8
     *  \brief Tests setting and getting int8
     *
     *  \return The actual value.
     */
    int8_t int8()
    {
        variable.template set<int8_t>(expectedInt8);
        return variable.template get<int8_t>();
    }

    /*
     *  \func uint8
     *  \brief Tests setting and getting uint8
     *
     *  \return The actual value.
     */
    uint8_t uint8()
    {
        variable.template set<uint8_t>(expectedUInt8);
        return variable.template get<uint8_t>();
    }

    /*
     *  \func int16
     *  \brief Tests setting and getting int16
     *
     *  \return The actual value.
     */
    int16_t int16()
    {
        variable.template set<int16_t>(expectedInt16);
        return variable.template get<int16_t>();
    }

    /*
     *  \func uint16
     *  \brief Tests setting and getting uint16
     *
     *  \return The actual value.
     */
    uint16_t uint16()
    {
        variable.template set<uint16_t>(expectedUInt16);
        return variable.template get<uint16_t>();
    }

    /*
     *  \func int32
     *  \brief Tests setting and getting int32
     *
     *  \return The actual value.
     */
    int32_t int32()
    {
        variable.template set<int32_t>(expectedInt32);
        return variable.template get<int32_t>();
    }

    /*
     *  \func uint32
     *  \brief Tests setting and getting uint32
     *
     *  \return The actual value.
     */
    uint32_t uint32()
    {
        variable.template set<uint32_t>(expectedUInt32);
        return variable.template get<uint32_t>();
    }

    /*
     *  \func int64
     *  \brief Tests setting and getting int64
     *
     *  \return The actual value.
     */
    int64_t int64()
    {
        variable.template set<int64_t>(expectedInt64);
        return variable.template get<int64_t>();
    }

    /*
     *  \func uint64
     *  \brief Tests setting and getting uint64
     *
     *  \return The actual value.
     */
    uint64_t uint64()
    {
        variable.template set<uint64_t>(expectedUInt64);
        return variable.template get<uint64_t>();
    }

    /*
     *  \func floatPres
     *  \brief Tests setting and getting float
     *
     *  \return The actual value.
     */
    float floatPres()
    {
        variable.template set<float>(expectedFloat);
        return variable.template get<float>();
    }

    /*
     *  \func doublePres
     *  \brief Tests setting and getting double
     *
     *  \return The actual value.
     */
    double doublePres()
    {
        variable.template set<double>(expectedDouble);
        return variable.template get<double>();
    }

    /*
     *  \func string
     *  \brief Tests setting and getting string
     *
     *  \return The actual value.
     */
    std::string string()
    {
        variable.template set<std::string>(expectedString);
        return variable.template get<std::string>();
    }

    std::string stdoutInt()
    {
        variable.template set<int32_t>(expectedInt32);
        return test::stdout(variable);
    }

    std::string stdoutFloat()
    {
        variable.template set<double>(expectedDouble);
        return test::stdout(variable);
    }

    std::string stdoutString()
    {
        variable.template set<std::string>(expectedString);
        return test::stdout(variable);
    }

    T variable;
    const int8_t expectedInt8;
    const uint8_t expectedUInt8;
    const int16_t expectedInt16;
    const uint16_t expectedUInt16;
    const int32_t expectedInt32;
    const uint32_t expectedUInt32;
    const int64_t expectedInt64;
    const uint64_t expectedUInt64;
    const float expectedFloat;
    const double expectedDouble;
    const std::string expectedString;
    const std::string expectedIntOut;
    const std::string expectedFloatOut;
    const std::string expectedStringOut;
};
}
}
