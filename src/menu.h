// Copyright <lwolmer, lshiela, jgerrick> 2022
#include <functional>
#include <iomanip>
#include <iostream>
#include "s21_graph_algorithms.h"

namespace s21 {
class Menu {
 public:
  void Start();
  Graph *GetGraph() const { return graph_.get(); };

 private:
  enum class MenuChoice {
    Quit,
    LoadGraphFromFile,
    BreadthFirstSearch,
    DepthFirstSearch,
    ShortestPathBetweenTwoVertices,
    ShortestPathsBetweenAllVertices,
    LeastSpanningTree,
    SolveTravelingSalesmanProblem,
    CompareAlgorithms
  };

  enum class TSMSolutionType { Ant, Annealing, Brute };

  int GetVariant(int min, int max);
  std::unique_ptr<Graph> graph_;
  GraphAlgorithms graph_algrthm_;
  void PrintMenu();
  void LoadGraphFromFile();
  void BreadthFirstSearch();
  void DepthFirstSearch();
  void ShortestPathBetweenTwoVertices();
  void ShortestPathsBetweenAllVertices();
  void LeastSpanningTree();
  void SolveTravelingSalesmanProblem(TSMSolutionType al_type,
                                     bool show_result = true);
  void MeasureTSMAlgorithmTime(std::function<void(TSMSolutionType, bool)> func,
                               TSMSolutionType type, std::size_t n);
  void CompareAlgorithms();
};
}  // namespace s21
