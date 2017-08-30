/*
 * Copyright (c) 2017 Clyde Stanfield
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
#include <iostream>
#include <exception>
#include <vector>
#include <string>
#include <nyra/game/twod/Stats.h>
#include <nyra/process/Subprocess.h>
#include <nyra/core/String.h>

using namespace nyra;

int main(int argc, char** argv)
{
    try
    {
        const auto distribution =
                game::twod::Stats::getDefaultDistribution();

        const double sigma = distribution.getStandardDeviation();
        const std::string script =
                "import matplotlib.pyplot as plt;"
                "import numpy as np;"
                "import matplotlib.mlab as mlab;"
                "import math;"
                "mu = " + core::str::toString(distribution.getMean()) + ";"
                "sigma = " + core::str::toString(sigma) + ";"
                "variance = " + core::str::toString(sigma * sigma) + ";"
                "x = np.linspace(mu-3*variance,mu+3*variance, 1000);"
                "plt.plot(x,mlab.normpdf(x, mu, sigma));"
                "plt.xlim([" + core::str::toString(distribution.getMin()) +
                " ," + core::str::toString(distribution.getMax()) + "]);"
                "plt.show()";
        std::cout << "python -c '" + script << "'\n";

        std::vector<std::string> args;
        args.push_back("-c");
        args.push_back(script);

        // TODO: This should be able run off the PATH.
        process::subprocess("/home/clyde/anaconda2/bin/python", args);
    }
    catch (const std::exception& ex)
    {
        std::cout << "STD Exception: " << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown Exception: System Error!" << std::endl;
    }

    return 0;
}
