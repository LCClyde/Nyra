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
#include <fstream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <nyra/xml/XML.h>


using namespace boost::property_tree;

namespace
{
//===========================================================================//
void readTree(const ptree& boostTree,
              const std::string& nodeName,
              nyra::mem::Tree<nyra::xml::Element>& tree)
{
    if (!boostTree.data().empty())
    {
        tree.get().text = boostTree.data();
    }

    std::unordered_map<std::string, std::vector<ptree::const_iterator> > posMap;
    for (ptree::const_iterator pos = boostTree.begin(); pos != boostTree.end(); ++pos)
    {
        // Check if we found attributes
        if (pos->first == "<xmlattr>")
        {
            for (ptree::const_iterator attr = pos->second.begin();
                 attr != pos->second.end();
                 ++attr)
            {
                if (!attr->second.data().empty())
                {
                    tree.get().attributes[attr->first] = attr->second.data();
                }
            }
        }
        else
        {
            posMap[pos->first].push_back(pos);
        }
    }

    for (auto iter = posMap.begin(); iter != posMap.end(); ++iter)
    {
        tree[iter->first] = new nyra::xml::Element();
        if (iter->second.size() == 1)
        {
            readTree(iter->second[0]->second,
                     iter->first, tree[iter->first]);
        }
        else
        {
            for (size_t ii = 0; ii < iter->second.size(); ++ii)
            {
                tree[iter->first][ii] = new nyra::xml::Element();
                readTree(iter->second[ii]->second,
                         iter->first, tree[iter->first][ii]);
            }
        }
    }
}

//===========================================================================//
void writeTree(const nyra::mem::Tree<nyra::xml::Element>& tree,
               ptree& boostTree)
{
    const auto keys = tree.keys();

    for (const std::string& key : keys)
    {
        if (tree[key].size() == 0)
        {
            boostTree.put(key, tree[key].get().text);

            // Add attributes
            // TODO: This is duplicate code
            for (auto iter = tree[key].get().attributes.begin();
                 iter != tree[key].get().attributes.end();
                 ++iter)
            {
                boostTree.put("<xmlattr>." + iter->first, iter->second);
            }

            writeTree(tree[key], boostTree.get_child(key));
        }
        else
        {
            for (size_t ii = 0; ii < tree[key].size(); ++ii)
            {
                ptree tempTree;
                tempTree.put_value(tree[key][ii].get().text);

                // Add attributes
                for (auto iter = tree[key][ii].get().attributes.begin();
                     iter != tree[key][ii].get().attributes.end();
                     ++iter)
                {
                    tempTree.put("<xmlattr>." + iter->first, iter->second);
                }

                writeTree(tree[key][ii], tempTree);
                boostTree.add_child(key, tempTree);
            }
        }
    }
}
}

namespace nyra
{
namespace xml
{
//===========================================================================//
XML::XML(const std::string& xmlString)
{
    std::stringstream ss;
    ss << xmlString;

    ptree boostTree;
    read_xml(ss, boostTree, xml_parser::trim_whitespace);
    readTree(boostTree, "", *this);
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os, const XML& tree)
{
    ptree boostTree;
    writeTree(tree, boostTree);

    xml_writer_settings<std::string> settings('\t', 1);
    write_xml(os, boostTree, settings);
    return os;
}
}

namespace core
{
//===========================================================================//
template <>
void write<xml::XML>(const xml::XML& tree,
                     const std::string& pathname,
                     core::ArchiveType)
{
    std::ofstream stream(pathname);
    stream << tree;
}

//===========================================================================//
template <>
void read<xml::XML>(const std::string& pathname,
                    xml::XML& tree,
                    core::ArchiveType)
{
    ptree boostTree;
    read_xml(pathname, boostTree, xml_parser::trim_whitespace);
    readTree(boostTree, "", tree);
}
}
}
