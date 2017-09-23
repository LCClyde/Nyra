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

//////////////////
//   0123456789  //
//  0ooxooooooo  //
//  1ooxooxoxxo  //
//  2ooxooxoxoo  //
//  3oxxooxxxoo  //
//  4oooooxoooo  //
///////////////////

//////////////////
//   0123456789  //
//  0Soxo------  //
//  1|oxo|xoxx|  //
//  2|oxo|xoxo|  //
//  3|xxo|xxxo|  //
//  4-----xoooE  //
///////////////////
TEST(Graph, Pathfinding)
{
    const Vector2I v00(0, 0);
    const Vector2I v01(0, 1);
    const Vector2I v02(0, 2);
    const Vector2I v03(0, 3);
    const Vector2I v04(0, 4);

    const Vector2I v10(1, 0);
    const Vector2I v11(1, 1);
    const Vector2I v12(1, 2);
    const Vector2I v14(1, 4);

    const Vector2I v24(2, 4);

    const Vector2I v30(3, 0);
    const Vector2I v31(3, 1);
    const Vector2I v32(3, 2);
    const Vector2I v33(3, 3);
    const Vector2I v34(3, 4);

    const Vector2I v40(4, 0);
    const Vector2I v41(4, 1);
    const Vector2I v42(4, 2);
    const Vector2I v43(4, 3);
    const Vector2I v44(4, 4);

    const Vector2I v50(5, 0);

    const Vector2I v60(6, 0);
    const Vector2I v61(6, 1);
    const Vector2I v62(6, 2);
    const Vector2I v64(6, 4);

    const Vector2I v70(7, 0);
    const Vector2I v74(7, 4);

    const Vector2I v80(8, 0);
    const Vector2I v82(8, 2);
    const Vector2I v83(8, 3);
    const Vector2I v84(8, 4);

    const Vector2I v90(9, 0);
    const Vector2I v91(9, 1);
    const Vector2I v92(9, 2);
    const Vector2I v93(9, 3);
    const Vector2I v94(9, 4);
    Graph<Vector2I> graph;

    // Add all up/down edges
    graph.addEdge(v00, v01);
    graph.addEdge(v01, v02);
    graph.addEdge(v02, v03);
    graph.addEdge(v03, v04);
    graph.addEdge(v10, v11);
    graph.addEdge(v11, v12);
    graph.addEdge(v30, v31);
    graph.addEdge(v31, v32);
    graph.addEdge(v32, v33);
    graph.addEdge(v33, v34);
    graph.addEdge(v40, v41);
    graph.addEdge(v41, v42);
    graph.addEdge(v42, v43);
    graph.addEdge(v43, v44);
    graph.addEdge(v60, v61);
    graph.addEdge(v61, v62);
    graph.addEdge(v82, v83);
    graph.addEdge(v83, v84);
    graph.addEdge(v90, v91);
    graph.addEdge(v91, v92);
    graph.addEdge(v92, v93);
    graph.addEdge(v93, v94);

    // Add all left/right edges
    graph.addEdge(v00, v10);
    graph.addEdge(v30, v40);
    graph.addEdge(v40, v50);
    graph.addEdge(v50, v60);
    graph.addEdge(v60, v70);
    graph.addEdge(v70, v80);
    graph.addEdge(v80, v90);
    graph.addEdge(v01, v11);
    graph.addEdge(v31, v41);
    graph.addEdge(v02, v12);
    graph.addEdge(v32, v42);
    graph.addEdge(v82, v92);
    graph.addEdge(v33, v43);
    graph.addEdge(v83, v93);
    graph.addEdge(v04, v14);
    graph.addEdge(v14, v24);
    graph.addEdge(v24, v34);
    graph.addEdge(v34, v44);
    graph.addEdge(v64, v74);
    graph.addEdge(v74, v84);
    graph.addEdge(v84, v94);

    Graph<Vector2I>::HeuristicEvent event;
    event = [](const Vector2I& v1, const Vector2I& v2)->double
            {return std::abs(v1.x - v2.x) + std::abs(v1.y - v2.y);};
    const auto results = graph.getPath(v00, v94, event);

    EXPECT_EQ(static_cast<size_t>(22), results.path.size());
    EXPECT_EQ(v00, results.path[0]);
    EXPECT_EQ(v94, results.path.back());

    for (size_t ii = 1; ii < results.path.size(); ++ii)
    {
        const size_t delta = event(results.path[ii], results.path[ii - 1]);
        EXPECT_EQ(static_cast<size_t>(1), delta);
    }



}
}
}

NYRA_TEST()
