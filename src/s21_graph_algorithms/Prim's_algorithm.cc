#include "s21_graph_algorithms.h"

namespace s21 {
Graph GraphAlgorithms::getLeastSpanningTree(Graph &graph) {
  int edge_count = 0;
  int graph_size = graph.Size();
  std::vector<bool> selected(static_cast<std::size_t>(graph_size), false);
  Graph result(graph_size);
  selected[0] = true;
  int y = 0;  //  row number
  int x = 0;  //  col number
  while (edge_count < graph_size - 1) {
    int min = std::numeric_limits<int>::max();
    for (int i = 0; i < graph_size; i++) {
      if (selected[static_cast<std::size_t>(i)]) {
        for (int j = 0; j < graph_size; j++) {
          if (!selected[static_cast<std::size_t>(j)] && graph(i, j) && graph(i, j) < min) {
              min = graph(i, j);
              y = i;
              x = j;
          }
        }
      }
    }
    result(x, y) = min;
    result(y, x) = min;
    selected[static_cast<std::size_t>(x)] = true;
    edge_count++;
  }
  return result;
}
}  //  namespace s21
