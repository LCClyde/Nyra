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
#include <nyra/mem/Tree.h>
#include <nyra/test/Test.h>

namespace
{
static std::string* globalParent = nullptr;
static std::string globalChild;
void onChildAddedFunc(std::string* parent, std::string& child)
{
    globalParent = parent;
    globalChild = child;
}
}

namespace nyra
{
namespace mem
{
TEST(Tree, Nodes)
{
    Tree<std::string> node;
    EXPECT_THROW(node["a"].get(), std::runtime_error);

    node["a"] = new std::string("The letter a");
    EXPECT_EQ("The letter a", node["a"].get());

    // Throw if you try to add unallocated nested nodes
    EXPECT_THROW(node["a"]["b"]["c"]["d"], std::runtime_error);

    node["a"]["b"] = new std::string();
    node["a"]["b"]["c"] = new std::string();
    node["a"]["b"]["c"]["d"] = new std::string("Nested");
    EXPECT_EQ("Nested", node["a"]["b"]["c"]["d"].get());

    for (size_t ii = 0; ii < 10; ++ii)
    {
        const std::string indexStr = "Index: " + std::to_string(ii);
        const std::string mapStr = "Map: " + std::to_string(ii);
        node["a"]["b"][ii] = new std::string(indexStr);
        node["a"]["b"][ii]["map"] = new std::string(mapStr);
        EXPECT_EQ(indexStr, node["a"]["b"][ii].get());
        EXPECT_EQ(mapStr, node["a"]["b"][ii]["map"].get());
        EXPECT_EQ(ii + 1, node["a"]["b"].size());
    }

    const Tree<std::string>& constNode = node;
    EXPECT_EQ("The letter a", constNode["a"].get());
    EXPECT_EQ("Index: 1", constNode["a"]["b"][1].get());

    // Accessing a unknown node in a const node should throw
    EXPECT_THROW(constNode["a2"], std::runtime_error);
    EXPECT_THROW(constNode["a"][3], std::runtime_error);
}

TEST(Tree, OnChild)
{
    Tree<std::string> node;
    node.onChildAdded = onChildAddedFunc;

    EXPECT_EQ(nullptr, globalParent);
    EXPECT_EQ("", globalChild);

    node["a"] = new std::string("Testing A");
    EXPECT_EQ(nullptr, globalParent);
    EXPECT_EQ("Testing A", globalChild);

    node["a"]["b"] = new std::string("Testing B");
    EXPECT_EQ("Testing A", *globalParent);
    EXPECT_EQ("Testing B", globalChild);
}
}
}

NYRA_TEST()
