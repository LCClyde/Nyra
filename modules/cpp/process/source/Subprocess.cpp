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
#include <boost/process.hpp>
#include <boost/asio.hpp>
#include <nyra/process/Subprocess.h>

namespace nyra
{
namespace process
{
void subprocess(const std::string& binary,
                const std::vector<std::string>& args,
                std::string& stdout,
                std::string& stderr)
{
    stdout = "";
    stderr = "";

    std::future<std::string> out;
    std::future<std::string> err;
    std::unique_ptr<boost::process::child> child;
    boost::asio::io_service ios;

    if (args.empty())
    {
        child.reset(new boost::process::child(
                binary,
                boost::process::std_in.close(),
                boost::process::std_out > out,
                boost::process::std_err > err,
                ios));
    }
    else
    {
        child.reset(new boost::process::child(
                binary,
                args,
                boost::process::std_in.close(),
                boost::process::std_out > out,
                boost::process::std_err > err,
                ios));
    }
    ios.run();

    stdout = out.get();
    stderr = err.get();
}
}
}
