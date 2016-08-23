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
#ifndef __NYRA_WIN_OGRE_WINDOW_H__
#define __NYRA_WIN_OGRE_WINDOW_H__

#include <OgreRenderWindow.h>
#include <nyra/win/Window.h>
#include <nyra/ogre/GlobalHandler.h>
#include <nyra/pattern/GlobalDependency.h>

namespace nyra
{
namespace win
{
namespace ogre
{
/*
 *  \class Window
 *  \brief Allows easy creation of Ogre windows that match the expected
 *         nyra interface for Windows.
 *         TODO: Ogre windows have massive problems.
 *               You cannot change the name after creation
 *               They autocreate a graphics handler with them
 *               Closing and reopening the window can sometimes lead to
 *               a seg fault.
 *               The position of the window is not reported correctly.
 *               The size of the window is rarely not reported correctly.
 *               The update is global so there is not fine grain control.
 *         WARNING: This class should be avoided because of all the issues.
 *                  Instead use a Qt window.
 */
class Window : public nyra::win::Window,
        private pattern::GlobalDependency<nyra::ogre::GlobalHandler>
{
public:
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
     *  \func Constructor
     *  \brief Move constructor
     *
     *  \param other The object to move
     */
    Window(Window&& other);

    /*
     *  \func Destructor
     *  \brief Closes the window when it falls out of scope.
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
     *  \brief Provides Ogre specific updates necessary for the OS.
     *         WARNING: Ogre has one common update for all windows. Because
     *         of this it is recommended to only call this in a window loop.
     */
    void update() override;

    /*
     *  \func close
     *  \brief Closes a window. The window should be considered invalid after
     *         being closed.
     *         WARNING: Ogre can crash if you open and close windows too often.
     */
    void close() override
    {
        if (mWindow)
        {
            getGlobalInstance().get()->destroyRenderTarget(mWindow);
            mWindow = nullptr;
        }
    }

    /*
     *  \func isOpen
     *  \brief Used to determine if a window is open and thus valid.
     *         WARNING: Ogre can crash if you open and close windows too often.
     *
     *  \return True if the window is currently open.
     */
    bool isOpen() const override
    {
        return mWindow && !mWindow->isClosed();
    }

    /*
     *  \func getName
     *  \brief Gets the name (title) of the window.
     *
     *  \return The name
     */
    std::string getName() const override
    {
        return mName;
    }

    /*
     *  \func getSize
     *  \brief Gets the size of the window. This represents the client size
     *         not the actual window size.
     *         WARNING: Rarely Ogre sends out an incorrect size.
     *
     *  \return The client size
     */
    math::Vector2U getSize() const override
    {
        unsigned int width;
        unsigned int height;
        unsigned int depth;
        int top;
        int left;
        mWindow->getMetrics(width, height, depth, left, top);
        return math::Vector2U(static_cast<uint32_t>(width),
                              static_cast<uint32_t>(height));
    }

    /*
     *  \func getPosition
     *  \brief Gets the window position in pixels from the top left corner of
     *         the primary monitor.
     *         WARNING: Ogre can send out an incorrect position.
     *
     *  \return The position in pixels
     */
    math::Vector2I getPosition() const override
    {
        unsigned int width;
        unsigned int height;
        unsigned int depth;
        int top;
        int left;
        mWindow->getMetrics(width, height, depth, left, top);
        return math::Vector2I(static_cast<int32_t>(left),
                              static_cast<int32_t>(top));
    }

    /*
     *  \func getHandle
     *  \brief Gets the operating system native handle for the window. This
     *         is platform specific.
     *         TODO: This is wrong on Linux
     *
     *  \return The OS specific window handle.
     */
    size_t getID() const override
    {
        void* id = nullptr;
#ifdef NYRA_WIN32
        mWindow->getCustomAttribute("HWND", id);
#else
        mWindow->getCustomAttribute("GLXWINDOW", id);
#endif
        return reinterpret_cast<size_t>(id);
    }

    /*
     *  \func getNative
     *  \brief Gets the underlying SDL object.
     *
     *  \return An Ogre object representing this window object.
     */
    const void* getNative() const override
    {
        return mWindow;
    }

    /*
     *  \func getNative
     *  \brief Same as above but non-const
     *
     *  \return An Ogre object representing this window object.
     */
    void* getNative() override
    {
        return mWindow;
    }

    /*
     *  \func setName
     *  \brief Ogre does not allow changing the window name.
     *         TODO: Find a way to do this with the window handle.
     *
     *  \param name The desired name.
     */
    void setName(const std::string& name) override
    {
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
        mWindow->reposition(position.x, position.y);
    }

private:
    Ogre::RenderWindow* mWindow;
    std::string mName;
};
}
}
}

#endif
