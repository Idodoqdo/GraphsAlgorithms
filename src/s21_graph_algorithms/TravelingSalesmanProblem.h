#pragma once
#include "s21_graph.h"
#include <memory>
#include <cmath>
#include <random>
#include <set>




namespace s21 {

struct TsmResult {
std::vector<std::size_t> vertices;
double distance;
};

class Ant {
    public:
    Ant(const Graph &graph_distance, std::unique_ptr<Graph> &graph_pheromones, std::size_t &index_start) : graph_distance_(graph_distance), 
    graph_pheromones_(graph_pheromones), gen_(rd_()), distrib_(0, 1) {
        run_result_.vertices.push_back(index_start);
        FillAvailablePlaces();
    };
    Ant() = delete;
    // пробег муравья по всем городам
    void Run();
    // сброс муравья до первоначального состояния
    void Reset(std::size_t &position);
    // выделение феромонов муравём
    void SecretePheromones();
    TsmResult get_result_() { return run_result_; }
    private:
    // переход в другой город
    void Transition(std::vector<double> & transition_probabilities_vec, std::vector<std::size_t> & where_can_go);

    // а куда он вообще сейчас может пойти?
    void FillingConnectedPoints(std::vector<std::size_t> & where);
    // расчёт вероятности перехода
    void TransitionDesireCalculation(std::vector<double> & transition_probabilities_vec, std::vector<std::size_t> & where_can_go);
    // расчет желания перехода в другой город
    void CalculateDesire(std::size_t index, double & result);
    // посчитаем города, куда он может ещё пойти
    const Graph & graph_distance_;
    std::unique_ptr<Graph> & graph_pheromones_;
    // куда муравей может зайти
    std::set<std::size_t> available_places_{};
    // заполнение индексов мест, куда можно пойти
    void FillAvailablePlaces();
    // для генерации случайного числа
    std::random_device rd_;
    std::mt19937 gen_;
    std::uniform_real_distribution<double> distrib_;
    // путь и размер дистацнии
    TsmResult run_result_{};
    // коэфы для рассчетов 
    const double kAlpha = 1;
    const double kBeta = 1;
    const double kQ = 1;
};

class Colony {
    public:
    Colony(const Graph & graph) : distance_between_points_graph_(graph) {
        pheromones_graph_ = std::make_unique<Graph>(graph.Size());
        FillPheromone();
    };

    Colony() = delete;
    //конструторы удалены, поскольку могут возникнуть проблемы при копировании объекта, содержащим unique_ptr
    Colony(const Colony&) = delete;
    Colony& operator=(const Colony&) = delete;
    void FindingShortestPath();
    TsmResult get_result_() { return result_;}

    private:
    // добавление нового муравья в колонию
    void CreateAnt(std::size_t index_start);
    // заполним граф феромонами
    void FillPheromone();
    // феромон постепенно испаряется
    void EvaporatePheromones();
    TsmResult result_{};
    // храним расстояние между точками
    const Graph & distance_between_points_graph_;
    // между городами будет раскидан феромон
    std::unique_ptr<Graph> pheromones_graph_{};
    // муравьишки, которые будут бегать по Игорю
    std::vector<std::unique_ptr<Ant>> ants_{};
    // коэф испарения
    const double kEvaporation = 0.64;
    const unsigned short kNumber_iterations = 100;
    const double kPheromones_start = 0.75;
};
}
