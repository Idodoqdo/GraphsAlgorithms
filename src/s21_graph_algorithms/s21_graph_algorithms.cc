#include "s21_graph_algorithms.h"

#include <bits/stdc++.h>

namespace s21 {
Graph GraphAlgorithms::getLeastSpanningTree(Graph &graph) {
  int edge_count = 0;  // number of edge
  // create a array to track selected vertex
  // selected will become true otherwise false
  int graph_size = graph.GetSize();
  std::vector<bool> selected(graph_size, false);
  Graph result(graph_size);

  // the number of egde in minimum spanning tree will be always
  //  less than (graph_size -1), where graph_size is number of vertices in graph

  // choose 0th vertex and make it true
  selected[0] = true;

  int y = 0;  //  row number
  int x = 0;  //  col number
  while (edge_count < graph_size - 1) {
    // For every vertex in the set S, find the all adjacent vertices
    //  , calculate the distance from the vertex selected at step 1.
    //  if the vertex is already in the set S, discard it otherwise
    // choose another vertex nearest to selected vertex  at step 1.

    int min = INT_MAX;

    for (int i = 0; i < graph_size; i++) {
      if (selected[i]) {
        for (int j = 0; j < graph_size; j++) {
          if (!selected[j] &&
              graph.GetEdge(i, j)) {  // not in selected and there is an edge
            if (graph.GetEdge(i, j) < min) {
              min = graph.GetEdge(i, j);
              y = i;
              x = j;
            }
          }
        }
      }
    }
    result.AddEdge(x, y, min);
    result.AddEdge(y, x, min);
    selected[x] = true;
    edge_count++;
  }
  return result;
}
}  //  namespace s21