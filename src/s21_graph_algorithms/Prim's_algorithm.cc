#include "s21_graph_algorithms.h"

#include <bits/stdc++.h>

namespace s21 {
Graph GraphAlgorithms::getLeastSpanningTree(Graph &graph) {
  int edge_count = 1;
  int graph_size = graph.GetSize();
  std::vector<bool> selected(graph_size + 1, false);
  Graph result(graph_size);
  selected[1] = true;
  int y = 1;  //  row number
  int x = 1;  //  col number
  while (edge_count < graph_size) {
    int min = std::numeric_limits::max();
    for (int i = 1; i <= graph_size; i++) {
      if (selected[i]) {
        for (int j = 1; j <= graph_size; j++) {
          if (!selected[j] && graph(i, j) && graph(i, j) < min) {
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
