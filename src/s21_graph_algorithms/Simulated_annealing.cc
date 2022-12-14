#include "s21_graph_algorithms.h"
namespace s21 {

TsmResult GraphAlgorithms::SimulatedAnnealint(const Graph &graph) {
        
    SimulatedAnnealing result(graph);
    result.FindSolution();
    return result.get_result_();
}

void SimulatedAnnealing::FindSolution() {
    RouteGeneration(); 
}

void SimulatedAnnealing::FindShortestPath() {
    
}

void SimulatedAnnealing::ChangeTwoPoints() {
    
}

void SimulatedAnnealing::FillingWhereCanGo(std::vector<size_t> & where_can_go, const std::set<size_t> & available) {
    for (auto i = available.cbegin(); i != available.cend(); ++i) {
        if (graph_(result_.vertices.back(), *i) > 0) where_can_go.push_back(*i);
    }
}

void SimulatedAnnealing::RouteGeneration() {
    auto available = FillingAvailablePlaces();
    for (size_t i = 0; i < graph_.Size(); ++i) {
        if (i == graph_.Size() - 1) available.insert(result_.vertices[0]);
        std::vector<size_t> where_can_go{};
        FillingWhereCanGo(where_can_go, available);
        ChooseRandomPlace(available, where_can_go);
    }
}

std::set<size_t> SimulatedAnnealing::FillingAvailablePlaces() {
    std::set<size_t> result{};
    for (size_t i = 0; i < graph_.Size(); ++i) {
        if (i != result_.vertices[0]) result.insert(i);
    }
    return result;
  }

void SimulatedAnnealing::ChooseRandomPlace(std::set<size_t> & available, const std::vector<size_t> & where_can_go) {
    size_t choice = static_cast<size_t>(rand_.GenerateRandomInt(0, static_cast<int>(where_can_go.size() - 1)));
    result_.distance += graph_(result_.vertices.back(), where_can_go[choice]);
    result_.vertices.push_back(where_can_go[choice]);
    available.erase(available.find(where_can_go[choice]));
}

}   