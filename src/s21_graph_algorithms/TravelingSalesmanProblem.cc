#include "s21_graph_algorithms.h"
#include "TravelingSalesmanProblem.h"
namespace s21 {
TsmResult GraphAlgorithms::solveTravelingSalesmanProblem(std::vector<std::vector<bool>> & graph) {
    
}

void Colony::CreateAnt(int index_start) {
    ants_.push_back(std::make_unique<Ant>(distance_between_points_graph_, pheromones_graph_, index_start));
}

void Ant::TransitionDesireCalculation() {
    std::vector<int> can_visit{};
    for (auto j = 0; j < graph_distance_.Size(); ++j) {
        if (std::find(tabu_.begin(), tabu_.end(), j) == tabu_.end()) {
        double desire = 0;
        double sum_all_desires = 0;
        CalculateDesire(j, desire);
        for (auto m = 0; m < graph_distance_.Size(); ++m) {
            if (std::find(tabu_.begin(), tabu_.end(), j) == tabu_.end()) CalculateDesire(m, sum_all_desires);
        }
        transition_probabilitys_vec_.push_back(desire/sum_all_desires);
        }
    }
}

void Ant::CalculatingCitiesToVisit(std::vector<int> & vec) {

}

void Ant::CalculateDesire(int index, double & result) {
    result += std::pow(graph_pheromones_->operator()(tabu_.back(), index), alfa_coeff)  * (1 / std::pow(graph_distance_(tabu_.back(), index), beta_coeff));
}

void Colony::FillFeromone() {
    for (auto i = 0; i < pheromones_graph_->Size(); ++i) {
        for (auto j = 0; j < pheromones_graph_->Size(); ++j) {
            if (i != j) {
                pheromones_graph_->operator()(i, j) = 0.2;
            }
        }
    }
}

}