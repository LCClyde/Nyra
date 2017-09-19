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
#ifndef __NYRA_MATH_GRAPH_H__
#define __NYRA_MATH_GRAPH_H__

#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/labeled_graph.hpp>
#include <boost/graph/astar_search.hpp>
#include <nyra/core/Event.h>

namespace nyra
{
namespace math
{
/*
 *  \class Graph
 *  \brief Creates a positional graph that is primarily used for pathfinding.
 *
 *  \tparam VectorT The vector type
 */
template <typename VectorT>
class Graph
{
private:
    struct Vertex
    {
        VectorT value;
    };

    typedef boost::property<boost::edge_weight_t, double> Weight;
    typedef boost::adjacency_list<boost::vecS,
                                  boost::vecS,
                                  boost::undirectedS,
                                  Vertex,
                                  Weight> UndirectedGraph;
    typedef boost::labeled_graph<UndirectedGraph, VectorT> GraphT;
    typedef typename UndirectedGraph::vertex_descriptor VertDesc;

public:
    /*
     *  \func addVertex
     *  \brief Adds a new unconnected vertex. In general you do not need to
     *         this unless you truly need an unconnected vertex. addEdge
     *         will call this for you for each new vertex it takes in.
     *
     *  \vert The vertex to add.
     */
    void addVertex(const VectorT& vert)
    {
        boost::add_vertex(vert, mGraph);
        mGraph[vert].value = vert;
    }

    /*
     *  \func addEdge
     *  \brief Adds a new edge. The edge is bidirectional meaning both v1
     *         and v2 will be neighbors to eachother.
     *
     *  \param v1 The first point. It will be added to the graph if it is new
     *  \param v2 The second point. It will be added to the graph if it is new
     */
    void addEdge(const VectorT& v1, const VectorT& v2)
    {
        if (!isValid(v1))
        {
            addVertex(v1);
        }

        if (!isValid(v2))
        {
            addVertex(v2);
        }
        boost::add_edge_by_label(v1, v2, (v2 - v2).length(), mGraph);
    }

    /*
     *  \func getNeighbors
     *  \brief Gets a list of neighbor nodes to a vertex
     *
     *  \param vec The point to get nodes from
     *  \return The list of nodes.
     */
    std::vector<VectorT> getNeighbors(const VectorT& vec) const
    {
        std::vector<VectorT> ret;
        typename UndirectedGraph::adjacency_iterator it, end;
        boost::tie(it, end) =
                boost::adjacent_vertices(mGraph.vertex(vec), mGraph.graph());
        for(; it != end; ++it)
        {
            ret.push_back(mGraph.graph()[*it].value);
        }
        return ret;
    }

    /*
     *  \type HeuristicEvent
     *  \brief Type used to evaluate a custom heuristic distance.
     */
    typedef core::Event<double(const VectorT& v1, const VectorT& v2)> HeuristicEvent;

private:
    class DistanceHeuristic : public boost::astar_heuristic<UndirectedGraph, double>
    {
    public:
        DistanceHeuristic(const UndirectedGraph& graph,
                          const VectorT& goal,
                          const HeuristicEvent& event) :
            mGraph(graph),
            mGoal(goal),
            mEvent(event)
        {
        }

        double operator()(VertDesc v)
        {
            return mEvent(mGoal, mGraph[v].value);
        }

        double func(const VectorT& v1, const VectorT& v2)
        {
            return std::abs(v1.x - v2.x) + std::abs(v1.y - v2.y);
        }

    private:
        const UndirectedGraph& mGraph;
        const VectorT mGoal;
        const HeuristicEvent& mEvent;
    };

    struct FoundGoal
    {
    };

    class GoalVisitor : public boost::default_astar_visitor
    {
    public:
        GoalVisitor(const VectorT& goal) :
            mGoal(goal)
        {
        }

        void examine_vertex(VertDesc vert, const UndirectedGraph& graph)
        {
            if(graph[vert].value == mGoal)
            {
                throw FoundGoal();
            }
        }
    private:
        const VectorT mGoal;
    };


public:
    /*
     *  \func getPath
     *  \brief Finds the shortest path using A*. This version using "as the
     *         crow flies" for its distance. This may not be optimal. Use
     *         the function below to specify your own heuristic.
     *
     *  \param start The starting node
     *  \param end The target node
     *  \return The path
     */
    std::vector<VectorT> getPath(const VectorT& start,
                                 const VectorT& end) const
    {
        HeuristicEvent event;
        event = [](const VectorT& v1, const VectorT& v2)->double
                {return (v1 - v2).length();};
        return getPath(start, end, event);
    }

    /*
     *  \func getPath
     *  \brief Finds the shortest path using A*. This version can always get
     *         the shortest path if you provide a good heuristic function.
     *
     *  \param start The starting node
     *  \param end The target node
     *  \param event The distance heuristic function
     *  \return The path
     */
    std::vector<VectorT> getPath(const VectorT& start,
                                 const VectorT& end,
                                 const HeuristicEvent& event) const
    {
        std::vector<VertDesc> verts(boost::num_vertices(mGraph));
        std::vector<double> costs(boost::num_vertices(mGraph));
        std::vector<VectorT> path;

        try
        {
            boost::astar_search(mGraph.graph(),
                                mGraph.vertex(start),
                                DistanceHeuristic(mGraph.graph(), end, event),
                                boost::predecessor_map(&verts[0]).
                                        distance_map(&costs[0]).
                                        visitor(GoalVisitor(end)));
        }
        catch (const FoundGoal& ex)
        {
            for(VertDesc v = mGraph.vertex(end); ; v = verts[v])
            {

                path.push_back(mGraph.graph()[v].value);
                if(verts[v] == v)
                {
                    break;
                }
            }
        }

        std::reverse(path.begin(), path.end());
        return path;
    }

private:
    bool isValid(const VectorT& v) const
    {
        typename UndirectedGraph::vertex_iterator it, end;
        boost::tie(it, end) =
                boost::vertices(mGraph.graph());

        // There may be a better way to do this.
        // It feels expensive
        for (; it != end; ++it)
        {
            if (mGraph.graph()[*it].value == v)
            {
                return true;
            }
        }
        return false;
    }

    GraphT mGraph;
};
}
}

#endif
