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
#ifndef __NYRA_CORE_ARCHIVE_H__
#define __NYRA_CORE_ARCHIVE_H__

#include <fstream>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/unordered_map.hpp>

namespace nyra
{
namespace core
{
/*
 *  \macro NYRA_SERIALIZE
 *  \brief Necessary to include serialization into a class. This separates us
 *         from boost in case we ever want to change systems, and matches
 *         the rest of the code base in terms of style.
 *         TODO: I don't want to use a macro here, but a typedef won't work
 *         with friend classes.
 */
#define NYRA_SERIALIZE() friend class boost::serialization::access;

/*
 *  \macro NYRA_SPLIT_SERIALIZE
 *  \brief Splits the serialize method into separate save / load methods.
 *         This separates us from boost in case we ever want to change
 *         systems, and matches the rest of the code base in terms of style.
 */
#define NYRA_SPLIT_SERIALIZE() \
NYRA_SERIALIZE() \
BOOST_SERIALIZATION_SPLIT_MEMBER()

/*
 *  \func writeArchive
 *  \brief Serializes an object to disk
 *
 *  \tparam The object type
 *  \param data The object to serialize
 *  \param pathname The location to write to
 */
template <typename T>
void writeArchive(const T& data, const std::string& pathname)
{
    std::ofstream outFile(pathname);
    boost::archive::text_oarchive archive(outFile);
    archive << data;
}

/*
 *  \func readArchive
 *  \brief Deserializes an object from disk. This version can be used
 *         on objects that can be assigned to.
 *
 *  \tparam T The object type
 *  \param pathname The file to read
 *  \param [OUTPUT] The data to load into
 */
template <typename T>
void readArchive(const std::string& pathname, T& data)
{
    std::ifstream inFile(pathname);
    boost::archive::text_iarchive archive(inFile);
    archive >> data;
}

/*
 *  \func readArchive
 *  \brief Deserializes an object from disk.
 *
 *  \tparam T The object type
 *  \param pathname The file to read
 *  \return The deserialzed object
 */
template <typename T>
T readArchive(const std::string& pathname)
{
    T data;
    readArchive(pathname, data);
    return data;
}
}
}

#endif
