// Copyright <lwolmer, lshiela, jgerrick> 2022
#ifndef SRC_S21_GRAPH_ALGORITHMS_H_
#define SRC_S21_GRAPH_ALGORITHMS_H_
#include <vector>
#include "ant_colony.h"
#include "brute_force.h"
#include "rand_generator.h"
#include "s21_graph.h"
#include "simulated_annealing.h"
#include "tsm.h"

namespace s21 {
class GraphAlgorithms {
 public:
  double getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  Graph getLeastSpanningTree(Graph &graph);
  std::vector<std::vector<double>> getShortestPathsBetweenAllVertices(
      Graph &graph);
  /**
      @brief A *non-recursive* depth-first search in the graph from a given
     vertex.

      @param graph Graph to search
      @param startVertex starting index
      @return std::vector<std::size_t> an array that contains the traversed
     vertices in the order they were traversed
  */
  std::vector<std::size_t> DepthFirstSearch(Graph &graph, int startVertex);
  /**
      @brief Breadth-first search in the graph from a given vertex.

      @param graph
      @param startVertex
      @return std::vector<std::size_t>
  */
  std::vector<std::size_t> BreadthFirstSearch(Graph &graph, int startVertex);
  TsmResult BruteForceAlg(const Graph &graph) {
    BruteForce temp(graph);
    temp.FindResult();
    return ++temp.result();
  };
  TsmResult solveTravelingSalesmanProblem(const Graph &graph) {
    Colony col(graph);
    col.FindingShortestPath();
    return ++col.result();
  }

  TsmResult SimulatedAnnealint(const Graph &graph) {
    SimulatedAnnealing result(graph);
    result.FindSolution();
    return ++result.result();
  }

  std::vector<std::size_t> SchortestPath(Graph &graph, std::size_t vertex1, std::size_t vertex2);

 private:
  std::vector<double> DijkstrasAlgorithm(Graph &graph, int vertex1);
  std::vector<std::size_t> RestoringPath(Graph &graph, std::vector<double> dist, std::size_t vertex1, std::size_t vertex2);
};

}  // namespace s21

#endif  // SRC_S21_GRAPH_ALGORITHMS_H_
