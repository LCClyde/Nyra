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
#include <nyra/mem/Tree.h>
#include <nyra/test/Test.h>

namespace
{
class TestNode
{
public:
    TestNode() = default;

    TestNode(const std::string& value) :
        value(value)
    {
    }

    bool operator==(const TestNode& other) const
    {
        return value == other.value;
    }

    std::string value;

private:
    NYRA_SERIALIZE()

    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & value;
    }
};

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

    node["a"] = new std::string("The letter a");
    EXPECT_EQ("The letter a", node["a"].get());

    // Throw if you try to add unallocated nested nodes
    EXPECT_THROW(node["a"]["b"]["c"]["d"], std::runtime_error);

    node["a"]["b"] = new std::string();
    node["a"]["b"]["c"] = new std::string();
    node["a"]["b"]["c"]["d"] = new std::string("Nested");
    EXPECT_EQ("Nested", node["a"]["b"]["c"]["d"].get());

    const Tree<std::string>& constNode = node;
    EXPECT_EQ("The letter a", constNode["a"].get());

    // Accessing a unknown node in a const node should throw
    EXPECT_THROW(constNode["a2"], std::runtime_error);
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

TEST(Tree, Stdout)
{
    Tree<std::string> node;
    EXPECT_EQ("{ }", test::stdout(node));

    node["a"] = new std::string();
    EXPECT_EQ("{ a : { } }", test::stdout(node));

    node["b"] = new std::string();
    node["c"] = new std::string();
    node["a"]["d"] = new std::string();
    node["a"]["e"] = new std::string();
    node["a"]["g"] = new std::string();

    // The order of the nodes cannot be known, so we just check the size
    // of the string
    EXPECT_EQ(static_cast<size_t>(63), test::stdout(node).size());
}
}
}

NYRA_TEST()
