#ifndef SRC_S21_GRAPH_ALGORITHMS_TSM_H_
#define SRC_S21_GRAPH_ALGORITHMS_TSM_H_
#include <vector>
namespace s21 {
struct TsmResult {
  std::vector<std::size_t> vertices;
  double distance;
  TsmResult operator++() {
    for (size_t i = 0; i < vertices.size(); ++i) vertices[i]++;
    return *this;
  }
};
}  // namespace s21

#endif  // SRC_S21_GRAPH_ALGORITHMS_TSM_H_
