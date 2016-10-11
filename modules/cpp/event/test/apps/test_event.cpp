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
#include <nyra/event/Event.h>
#include <nyra/test/Test.h>

namespace
{

double value = 0.0;

void voidFunction()
{
    value = 326.0;
}

void paramFunction(int x, double y)
{
    value = x / y;
}

void chainFunction(double x)
{
    value += x;
}

class Functor
{
public:
    void operator()() const
    {
        value = 9876.0;
    }

    void operator()(double x, double y, double z) const
    {
        value = x + y + z;
    }
};

}

namespace nyra
{
namespace event
{

TEST(Event, Call)
{
    Event voidFunc;
    voidFunc.add(voidFunction);
    voidFunc.call();
    EXPECT_EQ(326.0, value);

    Event paramFunc;
    paramFunc.add(paramFunction);
    paramFunc.call(150, 2.0);
    EXPECT_EQ(75.0, value);

    Event voidLambda;
    voidLambda.add([](){value = 225.0;});
    voidLambda.call();
    EXPECT_EQ(225.0, value);

    Event paramLambda;
    paramLambda.add<double, double>([](double x, double y){value = x * y;});
    paramLambda.call(20.0, 3.0);
    EXPECT_EQ(60.0, value);

    Event voidFunctor;
    voidFunctor.add(Functor());
    voidFunctor.call();
    EXPECT_EQ(9876.0, value);

    Event paramFunctor;
    paramFunctor.add<double, double, double>(Functor());
    paramFunctor.call<double, double, double>(1.0, 2.0, 3.0);
    EXPECT_EQ(6.0, value);
}

TEST(Event, Chain)
{
    Event chain;
    for (size_t ii = 0; ii < 10; ++ii)
    {
        chain.add(chainFunction);
    }
    value = 0.0;
    chain.call(100.0);
    EXPECT_EQ(1000.0, value);
}
}
}

NYRA_TEST()
