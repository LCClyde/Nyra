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
#ifndef __NYRA_WIN_NATIVE_WINDOW_POSIX_H__
#define __NYRA_WIN_NATIVE_WINDOW_POSIX_H__

#include <nyra/win/Window.h>
#include <nyra/win/native/PosixGlobalHandler.h>
#include <nyra/pattern/GlobalDependency.h>

namespace nyra
{
namespace win
{
namespace native
{
/*
 *  \class Window
 *  \brief Allows easy creation of X11 windows that match the expected
 *         nyra interface for Windows.
 */
class WindowPosix : public win::Window,
        private pattern::GlobalDependency<PosixGlobalHandler>
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a window. The default constructor will not actually
     *         open a Window. You must call load to create something.
     */
    WindowPosix();

    /*
     *  \func Constructor
     *  \brief Creates and opens a window.
     *
     *  \param name The name (title) of the window
     *  \param size The size of the window in pixels
     *  \param position The desired position of the window
     */
    WindowPosix(const std::string& name,
                const math::Vector2U& size = math::Vector2U(1280, 720),
                const math::Vector2I& position = math::Vector2I(0, 0));

    /*
     *  \func Constructor
     *  \brief Wrap an existing window into the nyra interface.
     *
     *  \param window A valid X11 window.
     */
    WindowPosix(::Window window);

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
     *  \brief Provides SFML specific updates necessary for the OS.
     */
    void update() override;

    /*
     *  \func close
     *  \brief Closes a window. The window should be considered invalid after
     *         being closed.
     */
    void close() override;

    /*
     *  \func isOpen
     *  \brief Used to determine if a window is open and thus valid.
     *
     *  \return True if the window is currently open.
     */
    bool isOpen() const override;

    /*
     *  \func getName
     *  \brief Gets the name (title) of the window.
     *
     *  \return The name
     */
    std::string getName() const override;

    /*
     *  \func getSize
     *  \brief Gets the size of the window. This represents the client size
     *         not the actual window size.
     *
     *  \return The client size
     */
    math::Vector2U getSize() const override;
    /*
     *  \func getPosition
     *  \brief Gets the window position in pixels from the top left corner of
     *         the primary monitor.
     *         NOTE: On Linux this does not take into account the decorators.
     *         as a result you do not get the correct results if you call
     *         setPosition and check it with this.
     *
     *  \return The position in pixels
     */
    math::Vector2I getPosition() const;

    /*
     *  \func getHandle
     *  \brief Gets the operating system native handle for the window. This
     *         is platform specific.
     *
     *  \return The OS specific window handle.
     */
    size_t getID() const override
    {
        return mWindow;
    }

    /*
     *  \func getNative
     *  \brief Gets the underlying SFML object.
     *
     *  \return An sf::RenderWindow representing this window object.
     */
    const void* getNative() const override
    {
        return reinterpret_cast<const void*>(mWindow);
    }

    /*
     *  \func getNative
     *  \brief Same as above but non-const
     *
     *  \return An sf::RenderWindow representing this window object.
     */
    void* getNative() override
    {
        return reinterpret_cast<void*>(mWindow);
    }

    /*
     *  \func setName
     *  \brief Sets the name (title) of the window.
     *
     *  \param name The desired name.
     */
    void setName(const std::string& name) override;

    /*
     *  \func setSize
     *  \brief Sets the size of the client area in pixels of the window.
     *
     *  \param size The desired size of the client area in pixels.
     */
    void setSize(const math::Vector2U& size);

    /*
     *  \func setPosition
     *  \brief Sets the position of the window in pixels from the top left
     *         corner of the primary monitor.
     *         NOTE: On Linux this takes the decorators into account and
     *         the matching get function does not.
     *
     *  \param position The desired position.
     */
    void setPosition(const math::Vector2I& position);

private:
    mutable ::Window mWindow;
    Atom mDeleteMessage;
};
}
}
}

#endif
