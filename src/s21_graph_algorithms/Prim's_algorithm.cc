#include "s21_graph_algorithms.h"

#include <bits/stdc++.h>

namespace s21 {
Graph GraphAlgorithms::getLeastSpanningTree(Graph &graph) {
  int edge_count = 1;
  int graph_size = graph.Size();
  std::vector<bool> selected(static_cast<std::size_t>(graph_size + 1), false);
  Graph result(graph_size);
  selected[1] = true;
  int y = 1;  //  row number
  int x = 1;  //  col number
  while (edge_count < graph_size) {
    int min = std::numeric_limits<int>::max();
    for (int i = 1; i <= graph_size; i++) {
      if (selected[static_cast<std::size_t>(i)]) {
        for (int j = 1; j <= graph_size; j++) {
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
