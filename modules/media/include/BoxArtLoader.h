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
#ifndef __NYRA_MEDIA_BOX_ART_LOADER_H__
#define __NYRA_MEDIA_BOX_ART_LOADER_H__

#include <string>
#include <vector>
#include <atomic>
#include <nyra/media/Game.h>

namespace nyra
{
namespace media
{
/*
 *  \func BoxArtLoader
 *  \brief Class that handles loading the box art. This can be called from
 *         a thread to allow everything to remain responsive while the
 *         art is loaded.
 */
class BoxArtLoader
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the BoxArtLoader
     *
     *  \param games The games to load
     *  \param boxArtPath The path to the box art.
     */
    BoxArtLoader(std::vector<Game>& games,
                 const std::string& boxArtPath);

    /*
     *  \func Functor
     *  \brief Starts the loading process. It is safe to call this from a
     *         thread. Call shutdown if you want to interrupt the process.
     */
    void operator()();

private:
    std::vector<Game>& mGames;
    const std::string mBoxArtPath;
};
}
}

#endif
