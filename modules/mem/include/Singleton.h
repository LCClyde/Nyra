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
#ifndef __NYRA_MEM_SINGLETON_H__
#define __NYRA_MEM_SINGLETON_H__

namespace nyra
{
namespace mem
{
/*
 *  \class Singleton
 *  \brief A wrapper to allow any class use the Singleton mem. This
 *         should be used as a last resort or for 3rd party objects that
 *         enforce only a single instance. This class is meant to be abstract
 *         and never instantiated by itself.
 *
 *  \tparam T The class to create a Singleton object for.
 */
template <typename T>
class Singleton
{
public:
    /*
     *  \func get
     *  \brief Gets the underlying Singleton object
     *
     *  \return The Singleton.
     */
    static T& get()
    {
        static T instance;
        return instance;
    }

private:
    // This class should never be instantiated.
    Singleton() = delete;
    Singleton(const Singleton&) = delete;
    Singleton(const Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(const Singleton&&) = delete;
    ~Singleton() = delete;
};
}
}
#endif
