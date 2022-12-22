#include "ant_colony.h"
#include <cmath>

namespace s21 {
void Colony::CreateAnt(std::size_t index_start) {
  ants_.push_back(std::make_unique<Ant>(distance_between_points_graph_,
                                        pheromones_graph_, index_start));
}

void Colony::EvaporatePheromones() {
  for (std::size_t i = 0; i < pheromones_graph_->Size(); i++) {
    for (std::size_t j = 0; j < pheromones_graph_->Size(); j++) {
      pheromones_graph_->operator()(i, j) *= kEvaporation;
    }
  }
}

void Colony::FindingShortestPath() {
  for (unsigned short l = 0; l < kNumber_iterations; ++l) {
    for (std::size_t i = 0; i < distance_between_points_graph_.Size(); ++i) {
      CreateAnt(i);
      ants_[i]->Run();
      if (i == 0) result_ = ants_[i]->result();
      if (ants_[i]->result().distance < result_.distance)
        result_ = ants_[i]->result();
    }
    EvaporatePheromones();
    for (std::size_t i = 0; i < distance_between_points_graph_.Size(); ++i) {
      ants_[i]->SecretePheromones();
      ants_[i]->Reset(i);
    }
  }
}

void Ant::TransitionDesireCalculation(
    std::vector<double> &transition_probabilities_vec,
    std::vector<std::size_t> &where_can_go) {
  for (auto j = where_can_go.begin(); j != where_can_go.end(); ++j) {
    double desire = 0;
    double sum_all_desires = 0;
    CalculateDesire(*j, desire);
    for (auto m = where_can_go.begin(); m != where_can_go.end(); ++m) {
      CalculateDesire(*m, sum_all_desires);
    }
    transition_probabilities_vec.push_back(desire / sum_all_desires);
  }
}

void Ant::Run() {
  for (std::size_t k = 0; k < graph_distance_.Size(); ++k) {
    if (k == graph_distance_.Size() - 1)
      available_places_.insert(run_result_.vertices[0]);
    std::vector<double> trans_prob{};
    std::vector<std::size_t> where_can_go{};
    FillingConnectedPoints(where_can_go);
    TransitionDesireCalculation(trans_prob, where_can_go);
    Transition(trans_prob, where_can_go);
  }
}

void Ant::FillingConnectedPoints(std::vector<std::size_t> &where) {
  for (auto i = available_places_.begin(); i != available_places_.end(); ++i) {
    if (graph_distance_(run_result_.vertices.back(), *i) > 0) {
      where.push_back(*i);
    }
  }
}

void Ant::Reset(std::size_t &position) {
  available_places_.clear();
  run_result_.distance = 0;
  run_result_.vertices.clear();
  run_result_.vertices.push_back(position);
  FillAvailablePlaces();
}

void Ant::Transition(std::vector<double> &transition_probabilities_vec,
                     std::vector<std::size_t> &where_can_go) {
  double random_choice = rand_.GenerateRandomDouble(0, 1);
  double choise_probability = 0;
  for (std::size_t i = 0; i < transition_probabilities_vec.size(); ++i) {
    choise_probability += transition_probabilities_vec[i];
    if (random_choice <= choise_probability) {
      run_result_.distance +=
          graph_distance_(run_result_.vertices.back(), where_can_go[i]);
      run_result_.vertices.push_back(where_can_go[i]);
      available_places_.erase(available_places_.find(where_can_go[i]));
      break;
    }
  }
}

void Ant::SecretePheromones() {
  double pheromone = kQ / run_result_.distance;
  for (std::size_t i = 0; i < run_result_.vertices.size() - 1; ++i) {
    graph_pheromones_->operator()(run_result_.vertices[i],
                                  run_result_.vertices[i + 1]) += pheromone;
  }
}

void Ant::FillAvailablePlaces() {
  for (std::size_t i = 0; i < graph_distance_.Size(); ++i) {
    if (i != run_result_.vertices[0]) {
      available_places_.insert(i);
    }
  }
}

void Ant::CalculateDesire(std::size_t index, double &result) {
  result += std::pow(graph_pheromones_->operator()(run_result_.vertices.back(),
                                                   index),
                     kAlpha) *
            (1 / std::pow(graph_distance_(run_result_.vertices.back(), index),
                          kBeta));
}

void Colony::FillPheromone() {
  for (std::size_t i = 0; i < pheromones_graph_->Size(); ++i) {
    for (std::size_t j = 0; j < pheromones_graph_->Size(); ++j) {
      if (i != j) {
        pheromones_graph_->operator()(i, j) = kPheromones_start;
      }
    }
  }
}
}  // namespace s21
