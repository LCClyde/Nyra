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
#ifndef __NYRA_MEDIA_PLATFORM_H__
#define __NYRA_MEDIA_PLATFORM_H__

#include <string>
#include <vector>
#include <nyra/core/Archive.h>

namespace nyra
{
namespace media
{
/*
 *  \class Platform
 *  \brief Information about a single platform
 */
struct Platform
{
public:
    /*
     *  \var name
     *  \brief The name of the platform
     */
    std::string name;

    /*
     *  \var extensions
     *  \brief A list of valid rom extensions
     */
    std::vector<std::string> extensions;

    /*
     *  \var goodTool
     *  \brief The name of the good tool used to verify the roms. If this
     *         is empty, there is no good tool.
     */
    std::string goodTool;

    /*
     *  \var goodMerge
     *  \brief The name of the good merge used to zip roms. If this is
     *         empty, there is no good merge.
     */
    std::string goodMerge;

private:
    friend std::ostream& operator<<(std::ostream& os,
                                    const Platform& platform);
};
}

namespace core
{
/*
 *  \func write
 *  \brief Writes a platform info to file.
 *
 *  \param platform The platform to save
 *  \param pathname The location to save to.
 *  \param type This will only write binary, even if you select something
 *         else
 */
template <>
void write<media::Platform>(const media::Platform& platform,
                            const std::string& pathname,
                            core::ArchiveType type);

/*
 *  \func read
 *  \brief Reads a platform info to file.
 *
 *  \param pathname The location to save to.
 *  \param platform The platform to load
 *  \param type This will only read binary, even if you select something
 *         else
 */
template <>
void read<media::Platform>(const std::string& pathname,
                           media::Platform& platform,
                           core::ArchiveType type);
}
}

#endif
