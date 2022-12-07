#pragma once
#include "../s21_graph/s21_graph.h"
#include <memory>
#include <cmath>
#include <algorithm>


namespace s21 {

struct TsmResult {
std::vector<int> vertices;
double distance;
};

double alfa_coeff = 1;
double beta_coeff = 1;

class Ant {
    public:
    Ant(const Graph & graph_distance, std::unique_ptr<Graph> & graph_pheromones, int index_start) : graph_distance_(graph_distance), 
    graph_pheromones_(graph_pheromones) {
        tabu_.push_back(index_start);
    };
    Ant() = delete;
    private:
    // расчёт вероятности перехода
    void TransitionDesireCalculation();
    // расчет желания перехода в другой город
    void CalculateDesire(int index, double & result);
    // посчитаем города, куда он может ещё пойти
    void CalculatingCitiesToVisit(std::vector<int> & vec);
    const Graph & graph_distance_;
    std::unique_ptr<Graph> & graph_pheromones_;
    // куда муравей уже заходил
    std::vector<int> tabu_{};
    // вектор вероятностей перехода
    std::vector<double> transition_probabilitys_vec_ {};
};

class Colony {
    public:
    Colony(const Graph & graph) : distance_between_points_graph_(graph) {
        pheromones_graph_ = std::make_unique<Graph>(graph.Size());
        FillFeromone();
    };

    Colony() = delete;
    //конструторы удалены, поскольку могут возникнуть проблемы при копировании объекта, содержащим unique_ptr
    Colony(const Colony&) = delete;
    Colony& operator=(const Colony&) = delete;

    private:
    // добавление нового муравья в колонию
    void CreateAnt(int index_start);
    // заполним граф феромонами
    void FillFeromone();
    TsmResult result{};
    // храним расстояние между точками
    const Graph & distance_between_points_graph_;
    // между городами будет раскидан феромон
    std::unique_ptr<Graph> pheromones_graph_{};
    // муравьишки, которые будут бегать по Игорю
    std::vector<std::unique_ptr<Ant>> ants_{};
};

}
