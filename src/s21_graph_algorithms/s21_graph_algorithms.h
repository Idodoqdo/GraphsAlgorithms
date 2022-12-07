// Copyright <lwolmer, lshiela, jgerrick> 2022
#include <vector>
#include "../s21_graph/s21_graph.h"
namespace s21 {
struct TsmResult {
std::vector<int> vertices;
double distance;
};

class Ant {
    Ant(const & Graph graph);
    Ant() = delete;
};

class GraphAlgorithms {
    public:
    TsmResult solveTravelingSalesmanProblem(std::vector<std::vector<bool>> &graph);
    private:
};
}
