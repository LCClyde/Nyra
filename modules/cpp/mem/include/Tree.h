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
#ifndef __NYRA_MEM_TREE_H__
#define __NYRA_MEM_TREE_H__

#include <vector>
#include <string>
#include <unordered_map>
#include <nyra/core/Event.h>

namespace nyra
{
namespace mem
{
template <typename TypeT>
class Tree
{
public:
    Tree() :
        mParent(nullptr),
        mRoot(this)
    {
    }

    Tree<TypeT>& operator[](const std::string& index)
    {
        validate();
        expand(index);
        return (*mMap[index]);
    }

    const Tree<TypeT>& operator[](const std::string& index) const
    {
        validate();
        const auto iter = mMap.find(index);
        if (iter == mMap.end())
        {
            throw std::runtime_error("Node: " + index + " does not exist.");
        }
        return *iter->second;
    }

    Tree<TypeT>& operator[](size_t index)
    {
        validate();
        expand(index);
        return *mList[index];
    }

    const Tree<TypeT>& operator[](size_t index) const
    {
        validate();

        if (index >= mList.size())
        {
            throw std::runtime_error(
                    "Index " + std::to_string(index) + " is out of bounds");
        }

        return *mList[index];
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
        RetT* ret = reinterpret_cast<RetT*>(mValue.get());

        if (!ret)
        {
            throw std::runtime_error("Value has not been initialized");
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
        RetT* ret = reinterpret_cast<RetT*>(mValue.get());

        if (!ret)
        {
            throw std::runtime_error("Value has not been initialized");
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
    Tree<TypeT>& operator=(TypeT* assignment)
    {
        mValue.reset(assignment);
        childAdded();
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
        for (const auto& iter : mMap)
        {
            keys.push_back(iter.first);
        }
        return keys;
    }

    core::Event<void(TypeT* parent, TypeT& child)> onChildAdded;

private:
    Tree(Tree<TypeT>* parent,
         Tree<TypeT>* root) :
        mParent(parent),
        mRoot(root)
    {
    }

    void childAdded()
    {
        mRoot->onChildAdded(
                mParent ? mParent->mValue.get() : nullptr, *mValue.get());

        // Loop through all the list children
        for (size_t ii = 0; ii < mList.size(); ++ii)
        {
            if (mList[ii].get() && mList[ii]->mValue.get())
            {
                mList[ii]->mParent = this;
                mRoot->onChildAdded(mValue.get(), (*mList[ii]->mValue.get()));
            }
        }

        // Loop through all the map children
        for (auto iter = mMap.begin(); iter != mMap.end(); ++iter)
        {
            if (iter->second.get() && iter->second.get()->mValue.get())
            {
                iter->second->mParent = this;
                mRoot->onChildAdded(mValue.get(),
                                    (*(iter->second->mValue.get())));
            }
        }
    }

    void expand(const std::string& index)
    {
        if (!(mMap[index].get()))
        {
            mMap[index].reset(new Tree<TypeT>(this, mRoot));
        }
    }

    void expand(size_t index)
    {
        if (mList.size() <= index)
        {
            const size_t prevSize = mList.size();
            mList.resize(index + 1);

            for (size_t ii = prevSize; ii < mList.size(); ++ii)
            {
                mList[ii].reset(new Tree<TypeT>(this, mRoot));
            }
        }
    }

    void validate() const
    {
        // Do not allow creation of children nodes unless this is set.
        if (!mValue.get() && mParent)
        {
            throw std::runtime_error(
                    "Node is not set and cannot create children.");
        }
    }

    typedef std::unordered_map<
            std::string, std::shared_ptr<Tree<TypeT> > > Map;
    typedef std::vector<std::shared_ptr<Tree<TypeT> > > List;

    Map mMap;
    List mList;
    std::unique_ptr<TypeT> mValue;

    Tree<TypeT>* mParent;
    Tree<TypeT>* const mRoot;
};
}
}

#endif
