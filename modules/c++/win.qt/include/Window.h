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
#ifndef __NYRA_WIN_QT_WINDOW_H__
#define __NYRA_WIN_QT_WINDOW_H__

#include <memory>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qapplication.h>
#include <nyra/win/Window.h>

namespace nyra
{
namespace win
{
namespace qt
{
/*
 *  \class Window
 *  \brief Allows easy creation of Qt windows that match the expected
 *         nyra interface for Windows.
 */
class Window : public nyra::win::Window
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a window. The default constructor will not actually
     *         open a Window. You must call load to create something.
     */
    Window();

    /*
     *  \func Constructor
     *  \brief Creates and opens a window.
     *
     *  \param name The name (title) of the window
     *  \param size The size of the window in pixels
     *  \param position The desired position of the window
     */
    Window(const std::string& name,
           const math::Vector2U& size,
           const math::Vector2I& position);

    /*
     *  \func Move Constructor
     *  \brief Moves a Qt Window from one object to the other. This will
     *         pass the "this" pointer to the new object which is used
     *         to manage the global Application object.
     *
     *  \param other The object to move.
     */
    Window(Window&& other);

    /*
     *  \func Destructor
     *  \brief Closes a window which in turn removes it reference from the
     *         Application object.
     */
    ~Window();

    /*
     *  \func load
     *  \brief Initializes a window. The window is considered invalid until
     *         this has been called. If the constructor with parameters is
     *         used, then this will be called under the hood.
     *
     *  \param name The desired name (title) of the window.
     *  \param size The desired client size of the window in pixels.
     *  \param position The position of the window in pixels from the top
     *         left corner of the primary monitor.
     */
    void load(const std::string& name,
              const math::Vector2U& size,
              const math::Vector2I& position) override;

    /*
     *  \func update
     *  \brief Provides Qt specific updates necessary for the OS.
     *         TODO: This needs to be tested with multiple windows to ensure
     *         it does not call multiple updates per frame.
     */
    void update() override;

    /*
     *  \func close
     *  \brief Closes a window. The window should be considered invalid after
     *         being closed. This will remove the window from the Application
     *         class. When the last window is removed the Application will
     *         be closed.
     */
    void close() override;

    /*
     *  \func isOpen
     *  \brief Used to determine if a window is open and thus valid.
     *
     *  \return True if the window is currently open.
     */
    bool isOpen() const override
    {
        return mWindow.get();
    }

    /*
     *  \func getName
     *  \brief Gets the name (title) of the window.
     *
     *  \return The name
     */
    std::string getName() const override
    {
        return mWindow->windowTitle().toUtf8().constData();
    }

    /*
     *  \func getSize
     *  \brief Gets the size of the window. This represents the client size
     *         not the actual window size.
     *
     *  \return The client size
     */
    math::Vector2U getSize() const override
    {
        return math::Vector2U(mWindow->geometry().width(),
                              mWindow->geometry().height());
    }

    /*
     *  \func getPosition
     *  \brief Gets the window position in pixels from the top left corner of
     *         the primary monitor.
     *
     *  \return The position in pixels
     */
    math::Vector2I getPosition() const override
    {
        return math::Vector2I(mWindow->x(),
                              mWindow->y());
    }

    /*
     *  \func getHandle
     *  \brief Gets the operating system native handle for the window. This
     *         is platform specific.
     *
     *  \return The OS specific window handle.
     */
    size_t getID() const override
    {
        return static_cast<size_t>(mWindow->winId());
    }

    /*
     *  \func getNative
     *  \brief Gets the underlying Qt object.
     *
     *  \return A QMainWindow representing this window object.
     */
    const void* getNative() const override
    {
        return mWindow.get();
    }

    /*
     *  \func getNative
     *  \brief Same as above but non-const
     *
     *  \return An QMainWindow representing this window object.
     */
    void* getNative() override
    {
        return mWindow.get();
    }

    /*
     *  \func setName
     *  \brief Sets the name (title) of the window.
     *
     *  \param name The desired name.
     */
    void setName(const std::string& name) override
    {
        mWindow->setWindowTitle(name.c_str());
    }

    /*
     *  \func setSize
     *  \brief Sets the size of the client area in pixels of the window.
     *
     *  \param size The desired size of the client area in pixels.
     */
    void setSize(const math::Vector2U& size) override
    {
        mWindow->resize(size.x, size.y);
    }

    /*
     *  \func setPosition
     *  \brief Sets the position of the window in pixels from the top left
     *         corner of the primary monitor.
     *
     *  \param position The desired position.
     */
    void setPosition(const math::Vector2I& position) override
    {
        mWindow->move(position.x, position.y);
    }

private:
    const void* const mHandle;
    std::unique_ptr<QMainWindow> mWindow;
};
}
}
}

#endif
