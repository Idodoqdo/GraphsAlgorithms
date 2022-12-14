#ifndef SRC_S21_SIMULATED_ANNEALING_H_
#define SRC_S21_SIMULATED_ANNEALING_H_
#include "s21_graph.h"

namespace s21 {
class SimulatedAnnealing {
 public:
    SimulatedAnnealing() = delete;
    SimulatedAnnealing(const Graph & graph) : graph_(graph) {
    };
    void FindSolution();
    TsmResult get_result_() {return result_;};
 private:
    std::set<size_t> FillingAvailablePlaces();
    const Graph & graph_;
    TsmResult result_{};
    RandomNumberGenerator rand_;
};
}
#endif // SRC_S21_SIMULATED_ANNEALING_H_