#include "simulated_annealing.h"
#include <algorithm>
#include <cmath>
namespace s21 {
void SimulatedAnnealing::FindSolution() {
  RouteGeneration();
  FindShortestPath();
}

void SimulatedAnnealing::FindShortestPath() {
  double alpha = 0.3;
  double temperature = 100;
  for (std::size_t i = 0; i < 100; ++i, temperature *= alpha) {
    TsmResult new_result = result_;
    ChangeTwoPoints(new_result.vertices);
    new_result.distance = DistanceCalculation(new_result.vertices);
    if (new_result.distance >= std::numeric_limits<double>::infinity())
      continue;
    double delta = new_result.distance - result_.distance;
    if (delta < 0) {
      result_ = new_result;
    } else {
      double P = 100 * std::pow(std::exp(1.0), -delta / temperature);
      if (P > rand_.GenerateRandomDouble(1, 100)) {
        result_ = new_result;
      }
    }
  }
}

double SimulatedAnnealing::DistanceCalculation(
    std::vector<std::size_t> const &vec) const {
  double result = 0;
  for (std::size_t i = 0; i < vec.size() - 1; ++i) {
    if (graph_(vec[i], vec[i + 1]) > 0)
      result += graph_(vec[i], vec[i + 1]);
    else
      result += std::numeric_limits<double>::infinity();
  }
  return result;
}

void SimulatedAnnealing::ChangeTwoPoints(std::vector<std::size_t> &new_path) {
  std::size_t first_index = static_cast<std::size_t>(rand_.GenerateRandomInt(
      1, static_cast<int>(result_.vertices.size() - 2)));
  std::size_t second_index = static_cast<std::size_t>(rand_.GenerateRandomInt(
      1, static_cast<int>(result_.vertices.size() - 2)));
  std::swap(new_path[first_index], new_path[second_index]);
}

void SimulatedAnnealing::FillingWhereCanGo(
    std::vector<std::size_t> &where_can_go,
    const std::set<std::size_t> &available) {
  for (auto i = available.cbegin(); i != available.cend(); ++i) {
    if (graph_(result_.vertices.back(), *i) > 0) where_can_go.push_back(*i);
  }
}

void SimulatedAnnealing::RouteGeneration() {
  auto available = FillingAvailablePlaces();
  for (std::size_t i = 0; i < graph_.Size(); ++i) {
    if (i == graph_.Size() - 1) available.insert(result_.vertices[0]);
    std::vector<std::size_t> where_can_go{};
    FillingWhereCanGo(where_can_go, available);
    ChooseRandomPlace(available, where_can_go);
  }
}

std::set<std::size_t> SimulatedAnnealing::FillingAvailablePlaces() {
  std::set<std::size_t> result{};
  for (std::size_t i = 0; i < graph_.Size(); ++i) {
    if (i != result_.vertices[0]) result.insert(i);
  }
  return result;
}

void SimulatedAnnealing::ChooseRandomPlace(
    std::set<std::size_t> &available,
    const std::vector<std::size_t> &where_can_go) {
  std::size_t choice = static_cast<std::size_t>(
      rand_.GenerateRandomInt(0, static_cast<int>(where_can_go.size() - 1)));
  result_.distance += graph_(result_.vertices.back(), where_can_go[choice]);
  result_.vertices.push_back(where_can_go[choice]);
  available.erase(available.find(where_can_go[choice]));
}

}  // namespace s21
