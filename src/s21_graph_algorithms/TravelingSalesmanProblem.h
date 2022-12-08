#pragma once
#include "../s21_graph/s21_graph.h"
#include <memory>
#include <cmath>
#include <random>
#include <set>




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
    graph_pheromones_(graph_pheromones), gen_(rd_()), distrib_(0, 1) {
        tabu_.push_back(index_start);
        FillAvailablePlaces();
    };
    Ant() = delete;
    // пробег муравья по всем городам
    void Run();

    private:
    // переход в другой город
    void Transition(std::vector<double> & transition_probabilitys_vec);
    // расчёт вероятности перехода
    void TransitionDesireCalculation(std::vector<double> & transition_probabilitys_vec);
    // расчет желания перехода в другой город
    void CalculateDesire(int index, double & result);
    // посчитаем города, куда он может ещё пойти
    const Graph & graph_distance_;
    std::unique_ptr<Graph> & graph_pheromones_;
    // куда муравей уже заходил
    std::vector<int> tabu_{};
    // куда муравей может зайти
    std::set<int> available_places_{};
    // заполнение индексов мест, куда можно пойти
    void FillAvailablePlaces();
    // для генерации случайного числа
    std::random_device rd_;
    std::mt19937 gen_;
    std::uniform_real_distribution<double> distrib_;
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
