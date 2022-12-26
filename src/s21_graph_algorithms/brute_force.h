// Copyright <lwolmer, lshiela, jgerrick> 2022
#ifndef SRC_S21_BRUTE_FORCE_H
#define SRC_S21_BRUTE_FORCE_H
#include <algorithm>
#include "s21_graph.h"
#include "tsm.h"

namespace s21 {
class BruteForce {
 public:
  explicit BruteForce(const Graph& graph) : graph_(graph) {}
  void FindResult() {
    result_.distance = std::numeric_limits<double>::max();
    for (std::size_t i = 0; i < graph_.Size(); ++i) {
      RouteGeneration(i);
    }
  }
  void RouteGeneration(std::size_t step, std::vector<std::size_t> route = {}, std::set<std::size_t> visited = {}) {
    route.push_back(step);
    visited.insert(step);
    auto connected = graph_.GetConnectedNodes(step);
    for(auto node : connected) {
      if (step == node || graph_(step, node) < std::numeric_limits<double>::epsilon())
        continue;
      if (visited.size() == graph_.Size()) {
        if (node == route.front()) {
          route.push_back(route.front());
          CalculateAndComparePath(route);
          return;
        }
      } else {
        if(visited.find(node) == visited.end())
          RouteGeneration(node, route, visited);
      }
    }
  };
  void CalculateAndComparePath(std::vector<std::size_t> &route) {
    double distance = 0;
    for(auto i = route.begin(); i != route.end(); ++i) {
      auto next = std::next(i);
      if (next != route.end())
        distance += graph_(*i, *next);
    }
    if (result_.distance > distance) {
      result_.distance = distance;
      result_.vertices = route;
    }
  }
  TsmResult result() const { return result_; }

 private:
  const Graph& graph_;
  TsmResult result_{};
};

}  // namespace s21
#endif  // SRC_S21_BRUTE_FORCE_H
