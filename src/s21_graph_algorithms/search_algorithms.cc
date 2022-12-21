// Copyright <lwolmer, lshiela, jgerrick> 2022
#include <algorithm>
#include <exception>
#include <set>
#include "s21_containers.h"
#include "s21_graph_algorithms.h"

namespace s21 {
std::vector<std::size_t> GraphAlgorithms::depthFirstSearch(Graph &graph,
                                                           int startVertex) {
  startVertex--;  // cuz readme constrains
  if (startVertex >= static_cast<int>(graph.Size()) || startVertex < 0)
    throw std::invalid_argument("incorrect startVertex argument");
  stack<std::size_t> stack_to_visit;
  std::set<std::size_t> plan_to_visit;
  for (std::size_t i = 0; i < graph.Size(); ++i) {
    plan_to_visit.insert(plan_to_visit.end(), i);
  }
  plan_to_visit.erase(static_cast<std::size_t>(startVertex));
  std::vector<std::size_t> visited;
  stack_to_visit.push(static_cast<std::size_t>(startVertex));
  while (!stack_to_visit.empty()) {
    std::size_t step_pos = stack_to_visit.top();
    stack_to_visit.pop();
    visited.push_back(step_pos + 1);
    auto connected = graph.GetConnectedNodes(step_pos);
    for (auto it = connected.rbegin(); it != connected.rend(); ++it) {
      // push only not visited
      if (plan_to_visit.find(*it) != plan_to_visit.end()) {
        plan_to_visit.erase(*it);
        stack_to_visit.push(*it);
      }
    }
  }
  return visited;
}

std::vector<std::size_t> GraphAlgorithms::breadthFirstSearch(Graph &graph,
                                                             int startVertex) {
  startVertex--;  // cuz readme constrains
  if (startVertex >= static_cast<int>(graph.Size()) || startVertex < 0)
    throw std::invalid_argument("incorrect startVertex argument");
  queue<std::size_t> queue_to_visit;
  std::set<std::size_t> plan_to_visit;
  for (std::size_t i = 0; i < graph.Size(); ++i) {
    plan_to_visit.insert(plan_to_visit.end(), i);
  }
  plan_to_visit.erase(static_cast<std::size_t>(startVertex));
  std::vector<std::size_t> visited;
  queue_to_visit.push(static_cast<std::size_t>(startVertex));
  while (!queue_to_visit.empty()) {
    std::size_t step_pos = queue_to_visit.front();
    queue_to_visit.pop();
    visited.push_back(step_pos + 1);
    auto connected = graph.GetConnectedNodes(step_pos);
    for (auto it = connected.begin(); it != connected.end(); ++it) {
      // push only not visited
      if (plan_to_visit.find(*it) != plan_to_visit.end()) {
        plan_to_visit.erase(*it);
        queue_to_visit.push(*it);
      }
    }
  }
  return visited;
}

}  // namespace s21