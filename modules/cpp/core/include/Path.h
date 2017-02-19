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
#ifndef __NYRA_CORE_PATH_H__
#define __NYRA_CORE_PATH_H__

#include <string>
#include <vector>

namespace nyra
{
namespace core
{
/*
 *  \var APPLICATION_PATH
 *  \brief The absolute path to the executable.
 *
 *  \throw If the definition of the application path is not supported on
 *         your platform.
 */
extern const std::string APPLICATION_PATH;

extern const std::string INSTALL_PATH;

extern const std::string DATA_PATH;

extern const std::string BINARY_PATH;

/*
 *  \namespace path
 *  \brief An extra namespace to help keep common functions outside of the
 *         nyra::core:: namespace. Other common modules such as str might
 *         have the functions with the same name.
 */
namespace path
{
/*
 *  \func split
 *  \brief Splits a path into it's parts.
 *
 *  \param input The path to split
 *  \return The parts of the path.
 */
std::vector<std::string> split(const std::string& input);

/*
 *  \func join
 *  \brief Joins to paths together and normalizes the result.
 *
 *  \param start The beginning of the path.
 *  \param end The desired end of the path.
 *  \return The joined path.
 */
std::string join(const std::string& start, const std::string& end);

/*
 *  \func exists
 *  \brief Returns true if the pathname exists on disk.
 *
 *  \param pathname The location on disk.
 *  \return True if the pathname exists.
 */
bool exists(const std::string& pathname);

/*
 *  \func listDirectory
 *  \brief Returns all files in a directory. This does not recurse and
 *         does not list sub directories.
 *         TODO: Add recurse and a directory flag when necessary.
 */
std::vector<std::string> listDirectory(const std::string& pathname);

/*
 *  \func getExtension
 *  \brief Returns the extension of a pathname. If the pathname does not
 *         have an extension, an empty string is returned.
 *
 *  \param pathname The pathname to pull the extension.
 *  \param iterations The maximum number of extensions to pull. If this is
 *         set to 0 all extensions are pulled. For example to get foo.tar.gz
 *         to return .tar.gz you need to set this to at least 2.
 *  \return The extension with the leading period or an empty string if
 *          there is no extension.
 */
std::string getExtension(const std::string& pathname,
                         size_t iterations = 0);

/*
 *  \func getBase
 *  \brief Gets the base of the filename.
 *
 *  \param pathname The pathname of the file
 *  \return The base name.
 */
std::string getBase(const std::string& pathname);

/*
 *  \func makeDirectory
 *  \brief Creates a directory recursively.
 *
 *  \param path The path to create the directory at.
 */
void makeDirectory(const std::string& path);

/*
 *  \func removeAll
 *  \brief Removes all contents in the path. This deletes the entire tree.
 *
 *  \param path The path to delete.
 */
void removeAll(const std::string& path);
}
}
}

#endif
