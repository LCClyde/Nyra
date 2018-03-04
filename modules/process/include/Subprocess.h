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
#ifndef __NYRA_PROCESS_SUBPROCESS_H__
#define __NYRA_PROCESS_SUBPROCESS_H__

#include <vector>
#include <string>

namespace nyra
{
namespace process
{
/*
 *  \func subprocess
 *  \brief Runs a subprocess synchronously.
 *
 *  \param binary The application to run
 *  \param args A list of arguments to pass. It is valid to pass in {}
 *  \param stdout [OUTPUT] The standard output from the application
 *  \param stderr [OUTPUT] The standard error from the application
 */
void subprocess(const std::string& binary,
                const std::vector<std::string>& args,
                std::string& stdout,
                std::string& stderr);

/*
 *  \func subprocess
 *  \brief Runs a subprocess synchronously.
 *
 *  \param binary The application to run
 *  \param args A list of arguments to pass.
 *  \param return The standard output from the application
 */
inline std::string subprocess(const std::string& binary,
                              const std::vector<std::string>& args = {})
{
    std::string stdout;
    std::string stderr;
    subprocess(binary, args, stdout, stderr);
    return stdout;
}
}
}

#endif
