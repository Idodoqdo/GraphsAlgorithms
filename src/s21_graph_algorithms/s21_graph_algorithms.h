// Copyright <lwolmer, lshiela, jgerrick> 2022
#include <vector>
namespace s21 {
struct TsmResult {
std::vector<int> vertices;
double distance;
};
class GraphAlgorithms {
    public:
    TsmResult solveTravelingSalesmanProblem(std::vector<std::vector<bool>> &graph);
    private:
};
}
