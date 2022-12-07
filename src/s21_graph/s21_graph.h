// Copyright <lwolmer, lshiela, jgerrick> 2022
#ifndef SRC_S21_GRAPH_S21_GRAPH_H_
#define SRC_S21_GRAPH_S21_GRAPH_H_
#include <string>
#include <vector>
#include <cassert>

namespace s21 {
class Graph {
 public:
  using matrix = std::vector<std::vector<int>>;
  Graph() = delete;
  explicit Graph(std::string & filepath);
  explicit Graph(int size);
  explicit Graph(int *matrix, int size);
  Graph(const Graph & other);

  int& operator ()(int x, int y) {
    int size = Size();
    assert(x >= 0 && y >= 0 && x < size && y < size);
    return matrix_[static_cast<std::size_t>(y)][static_cast<std::size_t>(x)];
  }

  const int& operator ()(int x, int y) const {
    int size = Size();
    assert(x >= 0 && y >= 0 && x < size && y < size);
    return matrix_[static_cast<std::size_t>(y)][static_cast<std::size_t>(x)];
  }
  
  int Size() const { return static_cast<int>(matrix_.size()); }
  /**
      @brief Loading a graph from a file in the adjacency matrix format

    @param filename Absolute Path to file
  */
  void LoadGraphFromFile(std::string &filename);
  /**
      @brief Exporting a graph to a dot file (see materials)
      
      @param filename Absolute Path to file
  */
  void ExportGraphToDot(std::string &filename);
 private:
  void AllocateMatrix(int size);
  bool CheckFormat(std::ifstream &stream, std::string reg);
  matrix matrix_;
};
}

#endif  // SRC_S21_GRAPH_S21_GRAPH_H_
