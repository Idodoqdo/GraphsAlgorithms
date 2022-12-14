#ifndef SRC_S21_SIMULATED_ANNEALING_H_
#define SRC_S21_SIMULATED_ANNEALING_H_
#include "s21_graph.h"

namespace s21 {
class SimulatedAnnealing {
 public:
    SimulatedAnnealing() = delete;
    SimulatedAnnealing(const Graph & graph) : graph_(graph) {
        result_.vertices.push_back(static_cast<size_t>(rand_.GenerateRandomInt(0, static_cast<int>(graph.Size() - 1))));
    };
    void FindSolution();
    TsmResult get_result_() {return result_;};
 private:
    std::set<size_t> FillingAvailablePlaces();
    void ChooseRandomPlace(std::set<size_t> & available, const std::vector<size_t> & where_can_go);
    void FillingWhereCanGo(std::vector<size_t> & where_can_go, const std::set<size_t> & available);
    void FindShortestPath();
    void ChangeTwoPoints();
    void RouteGeneration();
    const Graph & graph_;
    TsmResult result_{};
    RandomNumberGenerator rand_;
};
}
#endif // SRC_S21_SIMULATED_ANNEALING_H_