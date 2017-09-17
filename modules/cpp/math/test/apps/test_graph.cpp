/*
 * Copyright (c) 2016 Clyde Stanfield
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
#include <nyra/math/Graph.h>
#include <nyra/math/Vector2.h>
#include <nyra/test/Test.h>

namespace nyra
{
namespace math
{
TEST(Graph, Construction)
{
    Graph<Vector2F> graph;
    const Vector2F v1(100.0f, 100.0f);
    const Vector2F v2(90.0f, 80.0f);
    const Vector2F v3(50.0f, 10.0f);
    const Vector2F v4(80.0f, 90.0f);
    graph.addEdge(v1, v2);
    graph.addEdge(v1, v3);
    graph.addEdge(v1, v4);
    graph.addEdge(v3, v4);

    std::vector<Vector2F> res = graph.getNeighbors(v1);
    EXPECT_EQ(static_cast<size_t>(3), res.size());
    EXPECT_NE(std::find(res.begin(), res.end(), v2), res.end());
    EXPECT_NE(std::find(res.begin(), res.end(), v3), res.end());
    EXPECT_NE(std::find(res.begin(), res.end(), v4), res.end());

    res = graph.getNeighbors(v2);
    EXPECT_EQ(static_cast<size_t>(1), res.size());
    EXPECT_NE(std::find(res.begin(), res.end(), v1), res.end());

    res = graph.getNeighbors(v3);
    EXPECT_EQ(static_cast<size_t>(2), res.size());
    EXPECT_NE(std::find(res.begin(), res.end(), v1), res.end());
    EXPECT_NE(std::find(res.begin(), res.end(), v4), res.end());

    res = graph.getNeighbors(v4);
    EXPECT_EQ(static_cast<size_t>(2), res.size());
    EXPECT_NE(std::find(res.begin(), res.end(), v1), res.end());
    EXPECT_NE(std::find(res.begin(), res.end(), v3), res.end());
}
}
}

NYRA_TEST()
