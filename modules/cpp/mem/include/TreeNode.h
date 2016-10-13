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
#ifndef __NYRA_MEM_TREE_NODE_H__
#define __NYRA_MEM_TREE_NODE_H__

#include <unordered_map>
#include <memory>
#include <vector>
#include <string>
#include <nyra/core/Archive.h>
#include <nyra/mem/SetParent.h>

namespace nyra
{
namespace mem
{
/*
 *  \class TreeNode
 *  \brief Class that represents a node from the tree class. It can index
 *         into it's children
 */
template <typename TypeT>
class TreeNode
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a TreeNode
     *
     *  \param parent The parent tree node
     */
    TreeNode(const TreeNode<TypeT>* const parent = nullptr) :
        mParent(parent)
    {
    }

    /*
     *  \func Index Operator
     *  \brief Returns a child node. If the node does not exist, it will
     *         be created.
     *
     *  \param index The name of the child node
     *  \return The child node
     */
    TreeNode<TypeT>& operator[](const std::string& index)
    {
        if (!mChildren[index].get())
        {
            mChildren[index].reset(new TreeNode<TypeT>(this));
        }
        return *mChildren[index];
    }

    /*
     *  \func Index Operator
     *  \brief Returns a child node. Note this will throw if the node
     *         does not exist.
     *
     *  \param index The name of the child node
     *  \return The child node
     */
    const TreeNode<TypeT>& operator[](const std::string& index) const
    {
        const auto iter = mChildren.find(index);
        if (iter == mChildren.end())
        {
            throw std::runtime_error("Node: " + index + " does not exist.");
        }
        return *iter->second;
    }

    /*
     *  \func get
     *  \brief Gets the underlying object.
     *
     *  \tparam RetT The return type of the object.
     *  \return The object. This will be nullptr if it has never been
     *          assigned.
     */
    template <typename RetT = TypeT>
    RetT& get()
    {
        RetT* ret = reinterpret_cast<RetT*>(mNode.get());

        if (!ret)
        {
            throw std::runtime_error("Node has not been initialized");
        }
        return *ret;
    }

    /*
     *  \func get
     *  \brief Gets the underlying object.
     *
     *  \tparam RetT The return type of the object.
     *  \return The object. This will be nullptr if it has never been
     *          assigned.
     */
    template <typename RetT = TypeT>
    const RetT& get() const
    {
        RetT* ret = reinterpret_cast<RetT*>(mNode.get());

        if (!ret)
        {
            throw std::runtime_error("Node has not been initialized");
        }
        return *ret;
    }

    /*
     *  \func Assignment Operator
     *  \brief Assigns a pointer to the node. The node will take ownership
     *         of the pointer.
     *
     *  \param assignment The pointer to assign.
     *  \return The node object.
     */
    TreeNode<TypeT>& operator=(TypeT* assignment)
    {
        mNode.reset(assignment);
        setParent((*mNode),
                (mParent && mParent->mNode.get() ? &mParent->get() : nullptr));
        return *this;
    }

    /*
     *  \func keys
     *  \brief Gets a list of keys for this node.
     *
     *  \return The list of keys
     */
    std::vector<std::string> keys() const
    {
        std::vector<std::string> keys;
        for (const auto& iter : mChildren)
        {
            keys.push_back(iter.first);
        }
        return keys;
    }

private:
    NYRA_SERIALIZE()

    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & mNode;
        archive & mChildren;
    }

    friend std::ostream& operator<<(std::ostream& os,
                                    const TreeNode<TypeT>& node)
    {
        const std::vector<std::string> keys = node.keys();

        if (keys.empty())
        {
            os << "{ }";
        }
        else
        {
            for (const std::string& key : keys)
            {
                os << "{ " << key << " : " << node[key] << " }";
            }
        }
        return os;
    }

    typedef std::unordered_map<
            std::string, std::shared_ptr<TreeNode<TypeT> > > LeafMap;
    LeafMap mChildren;
    std::unique_ptr<TypeT> mNode;
    const TreeNode<TypeT>* const mParent;
};
}
}

#endif
