#include "s21_graph_algorithms.h"

namespace s21 {
Graph GraphAlgorithms::getShortestPathsBetweenAllVertices(Graph &graph) {
  double kEPS = 1e-7;
  size_t graph_size = graph.Size();
  Graph result(graph_size);
  result = graph;
    //Пробегаемся по всем вершинам и ищем более короткий путь
    //через вершину k
    for(size_t k = 0; k < graph_size; k++) {
        for(size_t i = 0; i < graph_size; i++) {
            for(size_t j = 0; j < graph_size; j++) {
                //Новое значение ребра равно минимальному между старым
                //и суммой ребер i <-> k + k <-> j (если через k пройти быстрее)

                // if ((result(i, k) > 0 && result(k, j) > 0 && i!=j)  || (result(i, j) < kEPS))
                // result(i, j) = std::min(result(i, j), result(i, k) + result(k, j));

                if ((result(i, j) > (result(i, k) + result(k, j)) || (result(i, j) < kEPS))
                    && (result(k, j) > 0 && result(i, k) > 0))
                    result(i, j) = result(i, k) + result(k, j);
            }
        }
    }
  return result;
}
}  //  namespace s21
