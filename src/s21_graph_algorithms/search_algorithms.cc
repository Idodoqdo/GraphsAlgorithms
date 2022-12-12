// Copyright <lwolmer, lshiela, jgerrick> 2022
#include "s21_graph_algorithms.h"
#include "s21_containers.h"
#include <set>
#include <algorithm>
#include <exception>
namespace s21 {
std::vector<std::size_t> GraphAlgorithms::DepthFirstSearch(Graph &graph, int startVertex) {
  startVertex--; // cuz readme constrains
  if (startVertex >= static_cast<int>(graph.Size()) || startVertex < 0)
    throw std::invalid_argument("incorrect startVertex argument");
  stack<std::size_t> stack;
  std::vector<std::size_t> visited;
  stack.push(static_cast<std::size_t>(startVertex));
  while (!stack.empty()) {
      std::size_t step = 0;
      step = stack.top();
      stack.pop();
      visited.push_back(step + 1);
      auto connected = graph.GetConnectedNodes(step);
      for (auto it = connected.rbegin(); it != connected.rend(); ++it) {
        // push only not visited
        if (std::find(visited.begin(), visited.end(), *it + 1) == visited.end())
          stack.push(*it);
      }
  }
  return visited;
}

std::vector<std::size_t> GraphAlgorithms::BreadthFirstSearch(Graph &graph, int startVertex) {
  std::cout << graph.Size() << startVertex;
  return std::vector<std::size_t>();
}

} // namespace s21