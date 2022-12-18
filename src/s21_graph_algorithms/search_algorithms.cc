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
  stack<std::size_t> not_visited;
  std::vector<std::size_t> visited;
  not_visited.push(static_cast<std::size_t>(startVertex));
  while (!not_visited.empty()) {
      std::size_t step_pos = not_visited.top();
      not_visited.pop();
      visited.push_back(step_pos + 1);
      auto connected = graph.GetConnectedNodes(step_pos);
      for (auto it = connected.rbegin(); it != connected.rend(); ++it) {
        // push only not visited
        if (std::find(visited.begin(), visited.end(), *it + 1) == visited.end())
          not_visited.push(*it);
      }
  }
  return visited;
}

std::vector<std::size_t> GraphAlgorithms::BreadthFirstSearch(Graph &graph, int startVertex) {
  startVertex--; // cuz readme constrains
  if (startVertex >= static_cast<int>(graph.Size()) || startVertex < 0)
    throw std::invalid_argument("incorrect startVertex argument");
  queue<std::size_t> not_visited;
  std::vector<std::size_t> visited;
  not_visited.push(static_cast<std::size_t>(startVertex));
  while (!not_visited.empty()) {
      std::size_t step_pos = not_visited.front();
      not_visited.pop();
      visited.push_back(step_pos + 1);
      auto connected = graph.GetConnectedNodes(step_pos);
      for (auto it = connected.begin(); it != connected.end(); ++it) {
        // push only not visited
        if (std::find(visited.begin(), visited.end(), *it + 1) == visited.end())
          not_visited.push(*it);
      }
  }
  return visited;
}

} // namespace s21