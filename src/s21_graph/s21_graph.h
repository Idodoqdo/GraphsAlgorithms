#ifndef SRC_S21_GRAPH_S21_GRAPH_H_
#define SRC_S21_GRAPH_S21_GRAPH_H_
#include <string>

namespace s21 {
class GraphAlgorithms () {
  public:
    /**
        @brief Loading a graph from a file in the adjacency matrix format

        @param filename Absolute Path to file
    */
    void LoadGraphFromFile(std::string filename);
    /**
        @brief Exporting a graph to a dot file (see materials)
        
        @param filename Absolute Path to file
    */
    void ExportGraphToDot(std::string filename);
}
}




#endif  // SRC_S21_GRAPH_S21_GRAPH_H_
