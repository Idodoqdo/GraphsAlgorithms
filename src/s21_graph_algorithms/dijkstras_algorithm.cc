#include <limits>
#include "s21_graph_algorithms.h"

namespace s21 {
double GraphAlgorithms::getShortestPathBetweenVertices(Graph &graph,
                                                       int vertex1,
                                                       int vertex2) {
  std::vector<double> tmp(graph.Size());
  tmp =  Dijkstras_algorithm(graph, vertex1);
  double result = tmp[static_cast<std::size_t>(vertex2 - 1)];
  return result;
}

std::vector<double> GraphAlgorithms::Dijkstras_algorithm(Graph &graph, int vertex1) {
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
  return dist;
}

std::vector<std::size_t> GraphAlgorithms::Restoring_the_path(Graph &graph, std::vector<double> dist, std::size_t vertex1, std::size_t vertex2) {

  if (dist[vertex2 - 1] < std::numeric_limits<double>::epsilon())
    throw std::runtime_error("Error! Vertices in the introduced graph are not connected!");

  // Восстановление пути
  std::vector<std::size_t> result(graph.Size(), 0);  // массив посещенных вершин
  result[0] = vertex2; // начальный элемент - конечная вершина

  double weight = dist[vertex2]; // вес конечной вершины
  std::size_t end = vertex2 - 1;
  std::size_t k = 1; // индекс предыдущей вершины
  while (end != vertex1 - 1 && k < graph.Size()) { // пока не дошли до начальной вершины
    for (std::size_t i = 0; i < graph.Size(); i++) // просматриваем все вершины
      if (graph(i, end) > std::numeric_limits<double>::epsilon()) {   // если связь есть (graph(i, end) != 0)
        double temp = weight - graph(i, end); // определяем вес пути из предыдущей вершины 
        if ((temp - dist.at(i)) < std::numeric_limits<double>::epsilon() && k < graph.Size()) { // если вес совпал с рассчитанным (temp == dist.at(i))
                         // значит из этой вершины и был переход
          weight = temp; // сохраняем новый вес
          end = i;       // сохраняем предыдущую вершину
          result.at(k) = i + 1; // и записываем ее в массив
          k++;
        }
      }
  }
  return result;  //  путь записан в обратном порядке т.к. шли с конца
}
}  // namespace s21
