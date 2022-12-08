#include "s21_graph_algorithms.h"
#include "TravelingSalesmanProblem.h"
namespace s21 {
TsmResult GraphAlgorithms::solveTravelingSalesmanProblem(std::vector<std::vector<bool>> & graph) {
    
}

void Colony::CreateAnt(int index_start) {
    ants_.push_back(std::make_unique<Ant>(distance_between_points_graph_, pheromones_graph_, index_start));
}

void Ant::TransitionDesireCalculation(std::vector<double> & transition_probabilitys_vec) {
    for (auto j = available_places_.begin(); j != available_places_.end(); ++j) {
        double desire = 0;
        double sum_all_desires = 0;
        CalculateDesire(*j, desire);
        for (auto m = available_places_.begin(); m != available_places_.end(); ++m) {
            CalculateDesire(*m, sum_all_desires);
        }
        transition_probabilitys_vec.push_back(desire/sum_all_desires);
    }
}

void Ant::Run() {
    for (auto k = 0; k < graph_distance_.Size(); ++k) {
        if (k == graph_distance_.Size() - 1) available_places_.insert(tabu_[0]);
        std::vector<double> trans_prob{};
        TransitionDesireCalculation(trans_prob);
        Transition(trans_prob);
    }
}

void Ant::Transition(std::vector<double> & transition_probabilitys_vec) {
    double random_choice = distrib_(gen_);
    for (unsigned i = 0; i < transition_probabilitys_vec.size(); ++i) {
        if (random_choice <= transition_probabilitys_vec[i]) {
            auto it = available_places_.begin();
            std::advance(it, i);
            tabu_.push_back(*it);
            available_places_.erase(it);
            break;
        }
    }
}

void Ant::FillAvailablePlaces() {
    for (auto i = 0; i < graph_distance_.Size(); ++i) {
        if (i != tabu_[0]) {
            available_places_.insert(i);
        }
    }
    // available_places_.erase(available_places_.find(tabu_[0]));  - оставим под вопросом
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