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
#ifndef __NYRA_WIN_WINDOW_H__
#define __NYRA_WIN_WINDOW_H__

#include <nyra/core/Archive.h>
#include <nyra/math/Vector2.h>

namespace nyra
{
namespace win
{
/*
 *  \class Window
 *  \brief An interface class used to represent an operating system window.
 */
class Window
{
public:
    /*
     *  \func Destructor
     *  \brief Necessary for inheritance.
     */
    virtual ~Window() = default;

    /*
     *  \func load
     *  \brief Initializes a window. The window is considered invalid until
     *         this has been called.
     *
     *  \param name The desired name (title) of the window.
     *  \param size The desired client size of the window in pixels.
     *  \param position The position of the window in pixels from the top
     *         left corner of the primary monitor.
     */
    virtual void load(const std::string& name,
                      const math::Vector2U& size,
                      const math::Vector2I& position) = 0;

    virtual void update() = 0;

    /*
     *  \func close
     *  \brief Closes a window. The window should be considered invalid after
     *         being closed.
     */
    virtual void close() = 0;

    /*
     *  \func isOpen
     *  \brief Used to determine if a window is open and thus valid.
     *
     *  \return True if the window is currently open.
     */
    virtual bool isOpen() const = 0;

    /*
     *  \func getName
     *  \brief Gets the name (title) of the window.
     *
     *  \return The name
     */
    virtual std::string getName() const = 0;

    /*
     *  \func getSize
     *  \brief Gets the size of the window. This represents the client size
     *         not the actual window size.
     *
     *  \return The client size
     */
    virtual math::Vector2U getSize() const = 0;

    /*
     *  \func getPosition
     *  \brief Gets the window position in pixels from the top left corner of
     *         the primary monitor.
     *
     *  \return The position in pixels
     */
    virtual math::Vector2I getPosition() const = 0;

    /*
     *  \func getID
     *  \brief Gets the operating system native handle for the window. This
     *         is platform specific.
     *
     *  \return The OS specific window handle.
     */
    virtual size_t getID() const = 0;

    /*
     *  \func getNative
     *  \brief An optional function that allows the user to get the underlying
     *         library specific object.
     *
     *  \return A library specific object.
     */
    virtual const void* getNative() const
    {
        return nullptr;
    }

    /*
     *  \func getNative
     *  \brief Same as above but non-const
     *
     *  \return A library specific object.
     */
    virtual void* getNative()
    {
        return nullptr;
    }

    /*
     *  \func setName
     *  \brief Sets the name (title) of the window.
     *
     *  \param name The desired name.
     */
    virtual void setName(const std::string& name) = 0;

    /*
     *  \func setSize
     *  \brief Sets the size of the client area in pixels of the window.
     *
     *  \param size The desired size of the client area in pixels.
     */
    virtual void setSize(const math::Vector2U& size) = 0;

    /*
     *  \func setPosition
     *  \brief Sets the position of the window in pixels from the top left
     *         corner of the primary monitor.
     *
     *  \param position The desired position.
     */
    virtual void setPosition(const math::Vector2I& position) = 0;

private:
    NYRA_SPLIT_SERIALIZE()

    template<class Archive>
    void save(Archive& archive, const unsigned int version) const
    {
        const bool open = isOpen();
        archive & open;
        if (open)
        {
            archive & getName();
            archive & getSize();
            archive & getPosition();
        }
    }

    template<class Archive>
    void load(Archive& archive, const unsigned int version)
    {
        bool open;
        archive & open;
        if (open)
        {
            std::string name;
            math::Vector2U size;
            math::Vector2I position;
            archive & name;
            archive & size;
            archive & position;
            load(name, size, position);
        }
        else
        {
            // If for some reason we try to load from an open window it
            // should close to match what we had.
            close();
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Window& window);
};
}
}

#endif
