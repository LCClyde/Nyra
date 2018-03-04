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
#include <iostream>
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <nyra/json/JSON.h>


using namespace boost::property_tree;

namespace
{
//===========================================================================//
void readTree(const ptree& boostTree,
              nyra::mem::Tree<std::string>& tree)
{
    if (!boostTree.data().empty())
    {
        tree = boostTree.data();
    }

    std::unordered_map<std::string, std::vector<ptree::const_iterator> > posMap;
    for (ptree::const_iterator pos = boostTree.begin(); pos != boostTree.end(); ++pos)
    {
        posMap[pos->first].push_back(pos);
    }

    for (auto iter = posMap.begin(); iter != posMap.end(); ++iter)
    {
        if (iter->second.size() == 1)
        {
            const ptree& newBoostTree = iter->second[0]->second;

            // If the name is empty, then this is a single list item
            if (iter->first.empty())
            {
                tree[0] = "";
                readTree(newBoostTree, tree[0]);
            }

            tree[iter->first] = "";
            readTree(newBoostTree, tree[iter->first]);
        }
        else
        {
            for (size_t ii = 0; ii < iter->second.size(); ++ii)
            {
                tree[ii] = "";
                readTree(iter->second[ii]->second, tree[ii]);
            }
        }
    }
}

//===========================================================================//
void writeTree(const nyra::mem::Tree<std::string>& tree,
               ptree& boostTree)
{
    const auto keys = tree.keys();

    for (const std::string& key : keys)
    {
        if (tree[key].size() == 0)
        {
            boostTree.put(key, tree[key].get());
            writeTree(tree[key], boostTree.get_child(key));
        }
        else
        {
            ptree children;
            if (!tree[key][0].get().empty())
            {
                for (size_t ii = 0; ii < tree[key].size(); ++ii)
                {
                    ptree child;
                    child.put("", tree[key][ii].get());
                    children.push_back(std::make_pair("", child));
                }

            }
            else
            {
                for (size_t ii = 0; ii < tree[key].size(); ++ii)
                {
                    ptree child;
                    writeTree(tree[key][ii], child);
                    children.push_back(std::make_pair("", child));
                }
            }
            boostTree.add_child(key, children);
        }
    }
}
}

namespace nyra
{
namespace json
{
//===========================================================================//
std::ostream& operator<<(std::ostream& os, const JSON& tree)
{
    ptree boostTree;
    writeTree(tree, boostTree);

    write_json(os, boostTree);
    return os;
}
}

namespace core
{
//===========================================================================//
template <>
void write<json::JSON>(const json::JSON& tree,
                       const std::string& pathname,
                       core::ArchiveType)
{
    std::ofstream stream(pathname);
    stream << tree;
}

//===========================================================================//
template <>
void read<json::JSON>(const std::string& pathname,
                      json::JSON& tree,
                      core::ArchiveType)
{
    ptree boostTree;
    read_json(pathname, boostTree);
    readTree(boostTree, tree);
}
}
}
