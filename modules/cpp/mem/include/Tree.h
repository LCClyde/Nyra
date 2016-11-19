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
#ifndef __NYRA_MEM_TREE_H__
#define __NYRA_MEM_TREE_H__

#include <vector>
#include <string>
#include <nyra/mem/TreeNode.h>
#include <nyra/core/Event.h>

namespace nyra
{
namespace mem
{
/*
 *  \class Tree
 *  \brief Class that can be used to create a tree of arbitrary objects. This
 *         is meant to be used with inheritance and can reset branch nodes
 *         to new classes efficiently.
 *
 *  \tparam TypeT The base class of the tree
 */
template <typename TypeT>
class Tree
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a default empty tree.
     */
    Tree() :
        mRoot(nullptr, onChildAdded)
    {
    }

    /*
     *  \func Index Operator
     *  \brief Gets a node in the tree. If the node does not exist than the it
     *         creates a NullT version.
     *
     */
    TreeNode<TypeT>& operator[](const std::string& index)
    {
        return mRoot[index];
    }

    /*
     *  \func Index Operator
     *  \brief Gets a node in the tree. If the node does not exist than this
     *         will throw. Use the non-const version if you need to insert.
     */
    const TreeNode<TypeT>& operator[](const std::string& index) const
    {
        return mRoot[index];
    }

    /*
     *  \func keys
     *  \brief Gets a list of keys for this node.
     *
     *  \return The list of keys
     */
    std::vector<std::string> keys() const
    {
        return mRoot.keys();
    }

    /*
     *  \var onChildAdded
     *  \brief Event that is fired whenever a new child node is add anywhere
     *         in the tree.
     */
    core::Event<void(TypeT* parent, TypeT& child)> onChildAdded;

private:
    friend std::ostream& operator<<(std::ostream& os, const Tree<TypeT>& tree)
    {
        const std::vector<std::string> keys = tree.keys();

        if (keys.empty())
        {
            os << "{ }";
        }
        else
        {
            for (const std::string& key : keys)
            {
                os << "{ " << key << " : " << tree[key] << " }";
            }
        }
        return os;
    }

    TreeNode<TypeT> mRoot;
};
}
}

#endif
