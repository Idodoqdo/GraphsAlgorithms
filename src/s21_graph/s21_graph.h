// Copyright <lwolmer, lshiela, jgerrick> 2022
#ifndef SRC_S21_GRAPH_S21_GRAPH_H_
#define SRC_S21_GRAPH_S21_GRAPH_H_
#include <string>
#include <vector>
#include <cassert>
#include <map>

namespace s21 {
class Graph {
 public:
  using matrix = std::vector<std::vector<double>>;
  Graph() = delete;
  explicit Graph(const std::string &filepath);
  explicit Graph(std::size_t size);
  explicit Graph(double *matrix, std::size_t size);

  double& operator ()(std::size_t x, std::size_t y) {
    return const_cast<double&>(const_cast<const Graph*>(this)->operator()(x, y));
  }
  const double& operator ()(std::size_t x, std::size_t y) const {
    std::size_t size = Size();
    assert(x < size && y < size);
    return matrix_[y][x];
  }  
  std::size_t Size() const { return matrix_.size(); }
  /**
      @brief Loading a graph from a file in the adjacency matrix format

    @param filename Absolute Path to file
  */
  void LoadGraphFromFile(const std::string& filename);
  /**
      @brief Exporting a graph to a dot file (see materials)
      
      @param filename Absolute Path to file
  */
  void ExportGraphToDot(const std::string& filename) const;
 private:
  void AllocateMatrix(std::size_t size);
  bool CheckFormat(std::ifstream &stream, std::string reg) const;
  std::multimap<double, std::pair<std::size_t, std::size_t>> GetAllPathsSortedByWeight() const;
  matrix matrix_;
};
}

#endif  // SRC_S21_GRAPH_S21_GRAPH_H_
