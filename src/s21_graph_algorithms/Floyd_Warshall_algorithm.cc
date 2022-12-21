#include <limits>

#include "s21_graph_algorithms.h"

namespace s21 {
std::vector<std::vector<double>>
GraphAlgorithms::getShortestPathsBetweenAllVertices(Graph &graph) {
  size_t graph_size = graph.Size();
  std::vector<std::vector<double>> result;
  result.resize(graph_size);
  for (std::size_t i = 0; i < graph_size; i++) {
    result[i].resize(graph_size, 0);
  }
  for (std::size_t y = 0; y < graph_size; y++) {
    for (std::size_t x = 0; x < graph_size; x++)
      result[y][x] = graph(x, y);
  }
  //Пробегаемся по всем вершинам и ищем более короткий путь
  //через вершину k
  for (size_t k = 0; k < graph_size; k++) {
    for (size_t i = 0; i < graph_size; i++) {
      for (size_t j = 0; j < graph_size; j++) {
        //Новое значение ребра равно минимальному между старым
        //и суммой ребер i <-> k + k <-> j (если через k пройти быстрее)
        if ((result[i][j] > (result[i][k] + result[k][j]) ||
             (result[i][j] < std::numeric_limits<double>::epsilon())) &&
            (result[k][j] > 0 && result[i][k] > 0) && i != j)
          result[i][j] = result[i][k] + result[k][j];
      }
    }
  }
  return result;
}
}  //  namespace s21
