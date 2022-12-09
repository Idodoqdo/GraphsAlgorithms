#include "s21_graph_algorithms.h"

namespace s21 {
Graph GraphAlgorithms::getLeastSpanningTree(Graph &graph) {
  size_t edge_count = 0;
  size_t graph_size = graph.Size();
  std::vector<bool> selected(graph_size, false);
  Graph result(graph_size);
  selected[0] = true;
  size_t y = 0;  //  row number
  size_t x = 0;  //  col number
  while (edge_count < graph_size - 1) {
    double min = std::numeric_limits<double>::max();
    for (size_t i = 0; i < graph_size; i++) {
      if (selected[i]) {
        for (size_t j = 0; j < graph_size; j++) {
          if (!selected[j] && graph(i, j) > 0 && graph(i, j) < min) {
              min = graph(i, j);
              y = i;
              x = j;
          }
        }
      }
    }
    result(x, y) = min;
    result(y, x) = min;
    selected[x] = true;
    edge_count++;
  }
  return result;
}
}  //  namespace s21
