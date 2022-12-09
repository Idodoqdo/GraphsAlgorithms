// Copyright <lwolmer, lshiela, jgerrick> 2022
#include <bits/stdc++.h>

#include "../s21_graph/s21_graph.h"

namespace s21 {
class GraphAlgorithms {
 public:
  int getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  Graph GraphAlgorithms::getLeastSpanningTree(Graph &graph);
};
}  // namespace s21
