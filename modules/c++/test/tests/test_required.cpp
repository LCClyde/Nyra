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
#include <nyra/test/Test.h>
#include <nyra/test/Required.h>

namespace
{
class Foo
{
public:
    Foo()
    {
    }

    Foo(const std::string& value) :
        mBar(value)
    {
    }

    bool operator==(const Foo& other) const
    {
        return mBar == other.mBar;
    }

    const std::string& get() const
    {
        return mBar;
    }

private:
    std::string mBar;

    friend class boost::serialization::access;
    template<class ArchiveT>
    void serialize(ArchiveT& ar, const unsigned int version)
    {
        ar & mBar;
    }
};

std::ostream& operator<<(std::ostream& os, const Foo& foo)
{
    os << foo.get();
    return os;
}
}

TEST(Required, Archive)
{
    Foo input("foo");
    Foo output = nyra::test::testArchive(input);
    EXPECT_EQ(input, output);
}

TEST(Required, Stdout)
{
    Foo input("foo");
    const std::string out = nyra::test::testStdout(input);
    EXPECT_EQ(out, "foo");
}

NYRA_TEST()
