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
#include <nyra/core/Event.h>
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

double returnFunction(double x)
{
    return x;
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

    double operator()(double x) const
    {
        return x;
    }
};

class MyClass
{
public:
    void testVoid() const
    {
        value = 9876.0;
    }

    void testParam(double x, double y, double z) const
    {
        value = x + y + z;
    }

    double testReturn(double x) const
    {
        return x;
    }
};

}

namespace nyra
{
namespace core
{

TEST(Event, Call)
{
    Event<void()> voidFunc;
    voidFunc = voidFunction;
    voidFunc();
    EXPECT_EQ(326.0, value);

    Event<void(int, double)> paramFunc;
    paramFunc = paramFunction;
    paramFunc(150, 2.0);
    EXPECT_EQ(75.0, value);

    Event<double(double)> returnFunc;
    returnFunc = returnFunction;
    EXPECT_EQ(32.0, returnFunc(32.0));

    Event<void()> voidLambda;
    voidLambda = [](){value = 225.0;};
    voidLambda();
    EXPECT_EQ(225.0, value);

    Event<void(double, double)> paramLambda;
    paramLambda = [](double x, double y){value = x * y;};
    paramLambda(20.0, 3.0);
    EXPECT_EQ(60.0, value);

    Event<double(double)> returnLambda;
    returnLambda = [](double x)->double {return x;};
    EXPECT_EQ(99.0, returnLambda(99.0));

    Event<void()> voidFunctor;
    voidFunctor = Functor();
    voidFunctor();
    EXPECT_EQ(9876.0, value);

    Event<void(double, double, double)> paramFunctor;
    paramFunctor = Functor();
    paramFunctor(1.0, 2.0, 3.0);
    EXPECT_EQ(6.0, value);

    Event<double(double)> returnFunctor;
    returnFunctor = Functor();
    EXPECT_EQ(546.0, returnFunctor(546.0));

    MyClass myClass;

    Event<void()> voidMember;
    voidMember = std::bind(&MyClass::testVoid, &myClass);
    voidMember();
    EXPECT_EQ(9876.0, value);

    Event<void(double, double, double)> paramMember;
    paramMember = std::bind(&MyClass::testParam,
                            &myClass,
                            std::placeholders::_1,
                            std::placeholders::_2,
                            std::placeholders::_3);
    paramMember(1.0, 2.0, 3.0);
    EXPECT_EQ(6.0, value);

    Event<double(double)> returnMember;
    returnMember = std::bind(&MyClass::testReturn,
                             &myClass,
                             std::placeholders::_1);
    EXPECT_EQ(546.0, returnMember(546.0));
}

TEST(Event, Reset)
{
    Event<double(double)> returnFunctor;
    returnFunctor = Functor();
    EXPECT_EQ(546.0, returnFunctor(546.0));

    returnFunctor.reset();
    EXPECT_EQ(0.0, returnFunctor(546.0));
}
}
}

NYRA_TEST()
