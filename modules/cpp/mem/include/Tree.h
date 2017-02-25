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
/*
 *  \class Tree
 *  \brief Class meant to mimic the functionality you can get from a Python
 *         dict / list. This supports both vector and map operations
 *         in a single container.
 *
 *  \tparam TypeT The element type. This can be a base class.
 */
template <typename TypeT>
class Tree
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the root node.
     */
    Tree() :
        mParent(nullptr),
        mRoot(this)
    {
    }

    /*
     *  \func Index operator
     *  \brief Gets the node at an index.
     *         If the node does not exist an attempt will be made to create it.
     *         This node must be set for that to finish.
     *
     *  \param index The desired node
     *  \return The node.
     */
    Tree<TypeT>& operator[](const std::string& index)
    {
        validate();
        expand(index);
        return (*mMap[index]);
    }

    /*
     *  \func Index operator
     *  \brief Gets the node at an index.
     *
     *  \param index The desired node
     *  \return The node.
     */
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

    /*
     *  \func Index operator
     *  \brief Gets the node at an index.
     *         If the node does not exist an attempt will be made to create it.
     *         This node must be set for that to finish.
     *
     *  \param index The desired node
     *  \return The node.
     */
    Tree<TypeT>& operator[](size_t index)
    {
        validate();
        expand(index);
        return *mList[index];
    }

    /*
     *  \func Index operator
     *  \brief Gets the node at an index. This does have a specialized function
     *         compared to the non-const version, in that if you pass in 0
     *         and there is no list, it will return itself. This allows
     *         you to loop over a 0 length tree. This will not work for the
     *         non-const version because it creates a new element.
     *
     *  \param index The desired node
     *  \return The node.
     */
    const Tree<TypeT>& operator[](size_t index) const
    {
        validate();

        // If the list is empty and index is 0, then we return ourselves.
        // this allows us to loop over a single element without knowing
        // if it really is a list.
        if (index == 0 && mList.size() == 0)
        {
            return *this;
        }

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
     *  \func valid
     *  \brief Returns true if the node is properly set
     *
     *  \return true if the node is valid and you can call get().
     */
    bool valid() const
    {
        return mValue.get();
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
     *  \func Assignment Operator
     *  \brief Assigns a reference to the node. The type must be copyable
     *         to use this assignment.
     *
     *  \param assignment The object to assign.
     *  \return The node object.
     */
    Tree<TypeT>& operator=(const TypeT& assignment)
    {
        mValue.reset(new TypeT(assignment));
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

    /*
     *  \func actualSize
     *  \brief Gets the real size of the list. The function "loopSize" will
     *         return 1 even if the size is 0. This is because it allows you
     *         to loop even when a list has not been created.
     *
     *  \return The actual size of the list
     */
    size_t size() const
    {
        return mList.size();
    }

    /*
     *  \func size
     *  \brief Gets the size of the list component. If the size is 0 this will
     *         return 1. By doing this it allows you to loop through a single
     *         element that would normally not be in the list.
     *
     *  \return The size of the list.
     */
    size_t loopSize() const
    {
        return std::max<size_t>(mList.size(), 1);
    }

    /*
     *  \func has
     *  \brief Returns true if the index is a child node
     *
     *  \param index The index to check
     *  \return true If the index is found.
     */
    bool has(const std::string& index) const
    {
        return mMap.find(index) != mMap.end();
    }

    /*
     *  \event onChildAdded
     *  \brief Occurs when a new child is added or a parent node is changed.
     */
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

    // TOOD: We should be allowed to set children nodes even if nothing is set.
    //       To do this, we need a smarter onChildAdded system.
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
