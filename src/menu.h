#include "s21_graph_algorithms.h"

class Menu {
 public:
  Menu() { graph_ = s21::Graph tmp(2); }
  void PrintMenu();
  int GetVariant(int capacity);
  void LoadGraphFromFile();
  void BreadthFirstSearch();
  void DepthFirstSearch();
  void ShortestPathBetweenTwoVertices();
  void ShortestPathsBetweenAllVertices();
  void LeastSpanningTree();
  void SolveTravelingSalesmanProblem();

 private:
  s21::Graph graph_;
};
