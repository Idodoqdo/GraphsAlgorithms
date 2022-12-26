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
    for (std::size_t start = 0; start < graph_.Size(); ++start) {
      std::vector<std::size_t> result = {};
      for (std::size_t i = 0; i < graph_.Size(); ++i) {
        result.push_back(i);
      }
      result.push_back(start);
      while (std::next_permutation(result.begin(), result.end())) {
        if (*result.begin() != *std::prev(result.end())) continue;
        std::size_t j = start;
        double temp_path = 0;
        for (std::size_t i = 1; i < result.size(); ++i) {
          if (graph_(j, result[i]) > 0) {
            temp_path += graph_(j, result[i]);
            j = result[i];
          } else {
            temp_path = std::numeric_limits<double>::max();
            break;
          }
        }
        temp_path += graph_(j, start);
        result_.distance = std::min(result_.distance, temp_path);
      };
    }
  }
  TsmResult result() const { return result_; }

 private:
  const Graph& graph_;
  TsmResult result_{};
};

}  // namespace s21
#endif  // SRC_S21_BRUTE_FORCE_H
