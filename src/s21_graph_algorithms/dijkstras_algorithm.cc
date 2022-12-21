#include <limits>
#include "s21_graph_algorithms.h"

namespace s21 {
double GraphAlgorithms::getShortestPathBetweenVertices(Graph &graph,
                                                       int vertex1,
                                                       int vertex2) {
  size_t graph_size = graph.Size();
  double max = std::numeric_limits<double>::max();
  std::vector<double> dist(static_cast<std::size_t>(graph_size), max);
  std::vector<bool> not_visited(static_cast<std::size_t>(graph_size), true);
  dist[static_cast<std::size_t>(vertex1 - 1)] = 0;
  size_t minindex;

  do {
    minindex = graph_size;
    double min = max;
    for (size_t i = 0; i < graph_size; i++) {
      // Если вершину ещё не обошли и вес меньше min
      if ((not_visited[i]) && (dist[i] < min)) {
        // Переприсваиваем значения
        min = dist[i];
        minindex = i;
      }
    }
    // Добавляем найденный минимальный вес
    // к текущему весу вершины
    // и сравниваем с текущим минимальным весом вершины
    if (minindex != graph_size) {
      for (size_t i = 0; i < graph_size; i++) {
        if (graph(minindex, i) > 0) {
          double temp = min + graph(minindex, i);
          if (temp < dist[i]) dist[i] = temp;
        }
      }
      not_visited[minindex] = false;
    }
  } while (minindex < graph_size);
  return dist[static_cast<std::size_t>(vertex2 - 1)];
}
}  // namespace s21
