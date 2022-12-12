// Copyright <lwolmer, lshiela, jgerrick> 2022
#include "s21_graph.h"

namespace s21 {
class GraphAlgorithms {
 public:
  double getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  Graph getLeastSpanningTree(Graph &graph);
  std::vector<std::vector<double>> getShortestPathsBetweenAllVertices(Graph &graph);
  /**
      @brief A *non-recursive* depth-first search in the graph from a given vertex.
      
      @param graph Graph to search
      @param startVertex starting index
      @return std::vector<std::size_t> an array that contains the traversed vertices in the order they were traversed
  */
  std::vector<std::size_t> DepthFirstSearch(Graph &graph, int startVertex);
};
}  // namespace s21
