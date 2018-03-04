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
#ifndef __NYRA_PROCESS_BACKGROUND_SUBPROCESS_H__
#define __NYRA_PROCESS_BACKGROUND_SUBPROCESS_H__

#include <vector>
#include <string>
#include <memory>
#include <future>
#include <thread>
#include <iostream>
#include <boost/process.hpp>
#include <boost/asio.hpp>

namespace nyra
{
namespace process
{
class BackgroundSubprocess
{
public:
    /*
     *  \func Constructor
     *  \brief Sets and runs the subprocess
     *
     *  \param binary The application to run
     *  \param args A list of arguments to pass.
     */
    BackgroundSubprocess(const std::string& binary,
                         const std::vector<std::string>& args = {});

    /*
     *  \func Destructor
     *  \brief Destroys the process.
     */
    ~BackgroundSubprocess();

    /*
     *  \func wait
     *  \brief Wait for the subprocess to finish
     */
    void wait()
    {
        if (mThread.joinable())
        {
            mThread.join();
        }
    }

    /*
     *  \func getStdOut
     *  \brief Gets the standard output. This blocks until the process is
     *         finished.
     *         TODO: Stream instead of block
     *
     *  \return The stdout
     */
    std::string getStdOut()
    {
        wait();
        return mStdOut.get();
    }

    /*
     *  \func getStdErr
     *  \brief Gets the standard error. This blocks until the process is
     *         finished.
     *         TODO: Stream instead of block
     *
     *  \return The stderr
     */
    std::string getStdErr()
    {
        wait();
        return mStdErr.get();
    }

    /*
     *  \func terminate
     *  \brief Forces the process to close.
     */
    void terminate()
    {
        mChild->terminate();
    }

    /*
     *  \func isRunning
     *  \brief Is the process running?
     *
     *  \return true If the processes is currently running.
     */
    bool isRunning() const
    {
        return mThread.joinable() && mChild->running();
    }

private:
    std::future<std::string> mStdOut;
    std::future<std::string> mStdErr;
    std::unique_ptr<boost::process::child> mChild;
    boost::asio::io_service mIOS;
    std::thread mThread;
};
}
}

#endif
