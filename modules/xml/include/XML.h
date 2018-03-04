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
#ifndef __NYRA_XML_XML_H__
#define __NYRA_XML_XML_H__

#include <nyra/mem/Tree.h>
#include <nyra/xml/Element.h>
#include <nyra/core/Archive.h>

namespace nyra
{
namespace xml
{
/*
 *  \type XML
 *  \brief Structure to store an XML document. Each element will be a key.
 *         List of elements will be indexed under the base key.
 */
class XML : public mem::Tree<Element>
{
public:
    /*
     *  \func Constructor
     *  \brief Creates an empty XML document
     */
    XML() = default;

    /*
     *  \func Constructor
     *  \brief Creates an XML from an XML string in memory
     *
     *  \param xmlString the XML to parse.
     */
    XML(const std::string& xmlString);

private:
    friend std::ostream& operator<<(std::ostream& os, const XML& tree);
};
}

namespace core
{
/*
 *  \func write
 *  \brief Serializes XML to disk
 *
 *  \param tree The XML object to serialize
 *  \param pathname The location to write to
 *  \param type The archive type is ignored. It will always write XML.
 */
template <>
void write<xml::XML>(const xml::XML& tree,
                     const std::string& pathname,
                     core::ArchiveType type);

/*
 *  \func read
 *  \brief Deserializes an XML object from disk.
 *
 *  \param pathname The file to read
 *  \param [OUTPUT] The data to load into
 *  \param type The archive type is ignored. It will always read XML.
 */
template <>
void read<xml::XML>(const std::string& pathname,
                    xml::XML& tree,
                    core::ArchiveType type);
}
}

#endif
