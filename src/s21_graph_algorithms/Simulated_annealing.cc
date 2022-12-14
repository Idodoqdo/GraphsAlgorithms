#include "s21_graph_algorithms.h"
namespace s21 {

TsmResult GraphAlgorithms::SimulatedAnnealint(const Graph &graph) {
        
    SimulatedAnnealing result(graph);
    result.FindSolution();
    return result.get_result_();
}

void SimulatedAnnealing::FindSolution() {
    auto available = FillingAvailablePlaces();
}

std::set<size_t> SimulatedAnnealing::FillingAvailablePlaces() {
    std::set<size_t> result{};
    for (size_t i = 0; i < graph_.Size(); ++i) {
        result.insert(i);
    }
    return result;
  }

}