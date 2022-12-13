// Copyright <lwolmer, lshiela, jgerrick> 2022

#include "../s21_graph/s21_graph.h"

namespace s21 {
class GraphAlgorithms {
 public:
  double getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  Graph getLeastSpanningTree(Graph &graph);
  std::vector<std::vector<double>> getShortestPathsBetweenAllVertices(Graph &graph);
};
}  // namespace s21
