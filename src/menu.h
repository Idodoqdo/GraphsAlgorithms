// Copyright <lwolmer, lshiela, jgerrick> 2022
#include <iostream>
#include <iomanip>

#include "s21_graph_algorithms.h"

namespace s21 {
class Menu {
 public:
  void Start();

 private:
  enum MenuChoice {
    kLoadGraphFromFile = 1,
    kBreadthFirstSearch,
    kDepthFirstSearch,
    kShortestPathBetweenTwoVertices,
    kShortestPathsBetweenAllVertices,
    kLeastSpanningTree,
    kSolveTravelingSalesmanProblem,
    Quit
  };

  std::size_t GetVariant(std::size_t capacity);
  void PrintMenu();
  void LoadGraphFromFile(Graph &graph);
  void BreadthFirstSearch();
  void DepthFirstSearch();
  void ShortestPathBetweenTwoVertices(Graph &graph, GraphAlgorithms &alg);
  void ShortestPathsBetweenAllVertices(Graph &graph, GraphAlgorithms &alg);
  void LeastSpanningTree(Graph &graph, GraphAlgorithms &alg);
  void SolveTravelingSalesmanProblem();
};
}  // namespace s21
