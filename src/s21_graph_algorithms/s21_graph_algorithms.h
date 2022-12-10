// Copyright <lwolmer, lshiela, jgerrick> 2022
#pragma once
#include <vector>
#include "TravelingSalesmanProblem.h"

#include "../s21_graph/s21_graph.h"
namespace s21 {
class GraphAlgorithms {
    public:
    TsmResult solveTravelingSalesmanProblem(const Graph &graph);
    double getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
    Graph getLeastSpanningTree(Graph &graph);
    private:
};
}

