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
#ifndef __NYRA_WIN_SFML_WINDOW_H__
#define __NYRA_WIN_SFML_WINDOW_H__

#include <memory>
#include <SFML/Graphics.hpp>
#include <nyra/win/Window.h>

namespace nyra
{
namespace win
{
namespace sfml
{
/*
 *  \class Window
 *  \brief Allows easy creation of SFML windows that match the expected
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
    void close() override
    {
        mWindow->close();
    }

    /*
     *  \func isOpen
     *  \brief Used to determine if a window is open and thus valid.
     *
     *  \return True if the window is currently open.
     */
    bool isOpen() const override
    {
        return mWindow->isOpen();
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
     *
     *  \return The client size
     */
    math::Vector2U getSize() const override
    {
        return math::Vector2U(mWindow->getSize());
    }

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
    math::Vector2I getPosition() const override
    {
        return math::Vector2I(mWindow->getPosition());
    }

    /*
     *  \func getHandle
     *  \brief Gets the operating system native handle for the window. This
     *         is platform specific.
     *
     *  \return The OS specific window handle.
     */
    size_t getID() const override;

    /*
     *  \func getNative
     *  \brief Gets the underlying SFML object.
     *
     *  \return An sf::RenderWindow representing this window object.
     */
    const void* getNative() const override
    {
        return mWindow.get();
    }

    /*
     *  \func getNative
     *  \brief Same as above but non-const
     *
     *  \return An sf::RenderWindow representing this window object.
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
        mWindow->setTitle(name);
        mName = name;
    }

    /*
     *  \func setSize
     *  \brief Sets the size of the client area in pixels of the window.
     *
     *  \param size The desired size of the client area in pixels.
     */
    void setSize(const math::Vector2U& size) override
    {
        mWindow->setSize(size.toThirdParty<sf::Vector2u>());
    }

    /*
     *  \func setPosition
     *  \brief Sets the position of the window in pixels from the top left
     *         corner of the primary monitor.
     *         NOTE: On Linux this takes the decorators into account and
     *         the matching get function does not.
     *
     *  \param position The desired position.
     */
    void setPosition(const math::Vector2I& position) override
    {
        mWindow->setPosition(position.toThirdParty<sf::Vector2i>());
    }

private:
    // Note: We use a unique_ptr here to allow this to be easily
    // movable. sf::RenderWindow destroys the window in the destructor.
    std::unique_ptr<sf::RenderWindow> mWindow;
    std::string mName;
};
}
}
}

#endif
