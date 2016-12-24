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
#ifndef __NYRA_EMU_MEMORY_TYPE_H__
#define __NYRA_EMU_MEMORY_TYPE_H__

namespace nyra
{
namespace emu
{
/*
 *  \class LongType
 *  \brief Used to determine what a word of twice the size would be.
 */
template <typename>
struct LongType
{
};

/*
 *  \class LongType<uint8_t>
 *  \brief Finds long type for uint8_t.
 */
template <>
struct LongType<uint8_t>
{
    /*
     *  \type LongT
     *  \brief uint16_t type
     */
    typedef uint16_t LongT;
};

/*
 *  \class LongType<uint16_t>
 *  \brief Finds long type for uint16_t.
 */
template <>
struct LongType<uint16_t>
{
    /*
     *  \type LongT
     *  \brief uint32_t type
     */
    typedef uint32_t longT;
};

/*
 *  \class LongType<uint32_t>
 *  \brief Finds long type for uint32_t.
 */
template <>
struct LongType<uint32_t>
{
    /*
     *  \type LongT
     *  \brief uint64_t type
     */
    typedef uint64_t LongT;
};
}
}

#endif
