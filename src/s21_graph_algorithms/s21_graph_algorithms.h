// Copyright <lwolmer, lshiela, jgerrick> 2022
#ifndef SRC_S21_GRAPH_ALGORITHMS_H_
#define SRC_S21_GRAPH_ALGORITHMS_H_
#include <vector>
#include "TravelingSalesmanProblem.h"

#include "../s21_graph/s21_graph.h"
namespace s21 {
class GraphAlgorithms {
  public:
  TsmResult solveTravelingSalesmanProblem(const Graph &graph);
  double getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  Graph getLeastSpanningTree(Graph &graph);
  std::vector<std::vector<double>> getShortestPathsBetweenAllVertices(Graph &graph);
  private:

  
};
}  // namespace s21

#endif  // SRC_S21_GRAPH_ALGORITHMS_H_