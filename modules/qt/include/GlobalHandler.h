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
#ifndef __NYRA_QT_GLOBAL_HANDLER_H__
#define __NYRA_QT_GLOBAL_HANDLER_H__

#include <memory>
#include <QApplication>
#include <nyra/mem/GlobalHandler.h>

namespace nyra
{
namespace qt
{
/*
 *  \class GlobalHandler
 *  \brief Global handler class for the QApplication. This must be created
 *         before any of Q* objects and must be deleted when you are done
 *         with them, but before static variables are deleted. The
 *         complexities of these interactions are hidden from the user in
 *         this class.
 *         TODO: This class does not have archive methods. As of now they
 *         seem unnecessary as its state is dependent on the state of
 *         Window objects.
 */
class GlobalHandler : public mem::GlobalHandler
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the arguments for the QApplication.
     */
    GlobalHandler();

    /*
     *  \func get
     *  \brief Gives access to the underlying QApplication.
     *
     *  \return The QApplication. This will be nullptr if no Qt is running.
     */
    QApplication* get()
    {
        return mApplication.get();
    }

    /*
     *  \func get
     *  \brief Gives access to the underlying QApplication.
     *
     *  \return The QApplication. This will be nullptr if no Qt is running.
     */
    const QApplication* get() const
    {
        return mApplication.get();
    }

private:
    void initializeGlobal() override;

    void shutdownGlobal() override;

    friend std::ostream& operator<<(std::ostream& os, const GlobalHandler& app);

    std::vector<char*> mArgv;
    int mArgc;
    std::unique_ptr<QApplication> mApplication;
};
}
}

#endif
