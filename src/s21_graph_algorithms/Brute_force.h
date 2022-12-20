// Copyright <lwolmer, lshiela, jgerrick> 2022
#ifndef SRC_S21_BRUTE_FORCE_H
#define SRC_S21_BRUTE_FORCE_H
#include "s21_graph.h"
#include "s21_graph_algorithms.h"
#include <algorithm>

namespace s21 {
class BruteForce {
 public:
  explicit BruteForce(const Graph & graph) : graph_(graph) {}
  void FindResult() {
    std::size_t source = 0;
    for (std::size_t i = 1; i < graph_.Size(); ++i) {
      result_.vertices.push_back(i);
    }
    result_.distance = std::numeric_limits<double>::max();
    while (std::next_permutation(result_.vertices.begin(), result_.vertices.end())) {
      std::size_t j = source;
      double temp_path = 0;
      for (std::size_t i = 0; i < result_.vertices.size(); ++i) {
        if (graph_(j, result_.vertices[i]) > 0) {
        temp_path += graph_(j, result_.vertices[i]);
        j = result_.vertices[i];
        } else {
          temp_path = std::numeric_limits<double>::max();
          break;
        }
      }
      temp_path += graph_(j, source);
      result_.distance = std::min(result_.distance, temp_path);
    };
  }
  TsmResult get_result_() {
    AddPlusOne();
    return result_ ;
    }

 private:
  const Graph & graph_;
  TsmResult result_{};
  void AddPlusOne() {
    for (size_t i = 0; i < result_.vertices.size(); ++i) {
      result_.vertices[i] += 1;
    }
  }

};

}
#endif  // SRC_S21_BRUTE_FORCE_H
