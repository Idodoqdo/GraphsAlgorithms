#include "s21_graph_algorithms.h"
#include "TravelingSalesmanProblem.h"
namespace s21 {
TsmResult GraphAlgorithms::solveTravelingSalesmanProblem(std::vector<std::vector<bool>> & graph) {
    
}

void Colony::CreateAnt(int index_start) {
    ants_.push_back(std::make_unique<Ant>(distance_between_points_graph_, pheromones_graph_, index_start));
}

void Colony::EvaporationPheromones() {
    for (auto i = 0; i < pheromones_graph_->Size(); ++i) {
        for (auto j = 0; j < pheromones_graph_->Size(); ++i) {
            pheromones_graph_->operator()(i, j) *= coeff_evaporation_;
        }        
    }
}

void Colony::FindingShortestPath() {
    for (unsigned short l = 0; l < 10; ++l) {
        for (int i = 0; i < distance_between_points_graph_.Size(); ++i) {
            CreateAnt(i);
            ants_[i]->Run();
        }
        EvaporationPheromones();
        for (int i = 0; i < distance_between_points_graph_.Size(); ++i) {
            ants_[i]->SecretePheromones();
            ants_[i]->Reset(i);
        }
    }
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
        if (k == graph_distance_.Size() - 1) available_places_.insert(run_result_.vertices[0]);
        std::vector<double> trans_prob{};
        TransitionDesireCalculation(trans_prob);
        Transition(trans_prob);
    }
}

void Ant::Reset(int &position) {
    available_places_.clear();
    run_result_.distance = 0;
    run_result_.vertices.clear();
    run_result_.vertices.push_back(position);
    FillAvailablePlaces();
}

void Ant::Transition(std::vector<double> & transition_probabilitys_vec) {
    double random_choice = distrib_(gen_);
    for (unsigned i = 0; i < transition_probabilitys_vec.size(); ++i) {
        if (random_choice <= transition_probabilitys_vec[i]) {
            auto it = available_places_.begin();
            std::advance(it, i);
            run_result_.distance += graph_distance_(run_result_.vertices.back(), *it);
            run_result_.vertices.push_back(*it);
            available_places_.erase(it);
            break;
        }
    }
}

void Ant::SecretePheromones() {
    double pheromone = q_coeff / run_result_.distance;
    for (auto i = 0; i < run_result_.vertices.size() - 1; ++i) {
        graph_pheromones_->operator()(run_result_.vertices[i], run_result_.vertices[i+1]) += pheromone;
    }
}

void Ant::FillAvailablePlaces() {
    for (auto i = 0; i < graph_distance_.Size(); ++i) {
        if (i != run_result_.vertices[0]) {
            available_places_.insert(i);
        }
    }
    // available_places_.erase(available_places_.find(run_result_.vertices[0]));  - оставим под вопросом
}

void Ant::CalculateDesire(int index, double & result) {
    result += std::pow(graph_pheromones_->operator()(run_result_.vertices.back(), index), alfa_coeff)  * (1 / std::pow(graph_distance_(run_result_.vertices.back(), index), beta_coeff));
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