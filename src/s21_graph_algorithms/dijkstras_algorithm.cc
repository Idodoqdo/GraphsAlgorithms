#include "s21_graph_algorithms.h"

namespace s21 {
int GraphAlgorithms::getShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                    int vertex2) {
  int graph_size = graph.Size();
  int max = std::numeric_limits<int>::max();
  std::vector<int> dist(static_cast<std::size_t>(graph_size), max);
  std::vector<bool> not_visited(static_cast<std::size_t>(graph_size), true);
  dist[static_cast<std::size_t>(vertex1 - 1)] = 0;
  int minindex;

  do {
    minindex = graph_size;
    int min = max;
    for (int i = 0; i < graph_size; i++) {
      // Если вершину ещё не обошли и вес меньше min
      if ((not_visited[static_cast<std::size_t>(i)]) && (dist[static_cast<std::size_t>(i)] < min)) {
        // Переприсваиваем значения
        min = dist[static_cast<std::size_t>(i)];
        minindex = i;
      }
    }
    // Добавляем найденный минимальный вес
    // к текущему весу вершины
    // и сравниваем с текущим минимальным весом вершины
    if (minindex != graph_size) {
      for (int i = 0; i < graph_size; i++) {
        if (graph(minindex, i) > 0) {
          int temp = min + graph(minindex, i);
          if (temp < dist[static_cast<std::size_t>(i)])
            dist[static_cast<std::size_t>(i)] = temp;
        }
      }
      not_visited[static_cast<std::size_t>(minindex)] = false;
    }
  } while (minindex < graph_size);
  return dist[static_cast<std::size_t>(vertex2 - 1)];
}
}  // namespace s21
