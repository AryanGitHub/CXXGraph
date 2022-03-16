#include <benchmark/benchmark.h>
#include <unistd.h>
#include "CXXGraph.hpp"
#include "Utilities.hpp"

static auto nodes = generateRandomNodes(100000, 2);
static auto edges = generateRandomEdges(100000, nodes);

static CXXGRAPH::Graph<int> *graph;

static void GraphCreation(benchmark::State &state)
{
    for (auto _ : state){
        CXXGRAPH::Graph<int> g;
    }
}

BENCHMARK(GraphCreation);

static void AddEdge(benchmark::State &state)
{
    CXXGRAPH::Graph<int> g;
    auto n1 = *nodes.at(0);
    auto n2 = *nodes.at(1);
    CXXGRAPH::Edge<int> e(1, n1, n2);
    for (auto _ : state)
    {
        g.addEdge(&e);
    }
}
BENCHMARK(AddEdge);

static void AddEdgeX(benchmark::State &state)
{
    CXXGRAPH::Graph<int> g;
    auto range_start = edges.begin();
    auto range_end = edges.find(state.range(0));
    std::unordered_map<unsigned long, CXXGRAPH::Edge<int> *> edgesX;
    edgesX.insert(range_start, range_end);
    for (auto _ : state)
    {
        for (auto e : edgesX)
        {
            g.addEdge(&(*e.second));
        }
    }
}
BENCHMARK(AddEdgeX)->RangeMultiplier(16)->Range((unsigned long)1, (unsigned long)1 << 16);
