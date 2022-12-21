// Copyright <lwolmer, lshiela, jgerrick> 2022
#include "menu.h"
#include <chrono>
#include <iterator>
namespace {
template<typename Iterator>
void SeparatedContainerPrint(Iterator begin, Iterator end, std::string separator) {
  if (begin != end) {
    Iterator last = std::prev(end);
    for (Iterator i = begin; i != end; ++i) {
      std::cout << *i;
      if (i != last)
        std::cout << separator;
    }
  }
}
}

namespace s21 {
void Menu::Start() {
  MenuChoice variant;  // выбранный пункт меню
  do {
    this->PrintMenu();  // выводим меню на экран
    // получаем номер выбранного пункта меню
    variant = static_cast<MenuChoice>(this->GetVariant(static_cast<int>(MenuChoice::Quit), static_cast<int>(MenuChoice::CompareAlgorithms)));
    switch (variant) {
      case MenuChoice::LoadGraphFromFile:
        this->LoadGraphFromFile();
        break;
      case MenuChoice::BreadthFirstSearch:
        this->BreadthFirstSearch();
        break;
      case MenuChoice::DepthFirstSearch:
        this->DepthFirstSearch();
        break;
      case MenuChoice::ShortestPathBetweenTwoVertices:
        this->ShortestPathBetweenTwoVertices();
        break;
      case MenuChoice::ShortestPathsBetweenAllVertices:
        this->ShortestPathsBetweenAllVertices();
        break;
      case MenuChoice::LeastSpanningTree:
        this->LeastSpanningTree();
        break;
      case MenuChoice::SolveTravelingSalesmanProblem:
        this->SolveTravelingSalesmanProblem(TSMSolutionType::Ant);
        break;
      case MenuChoice::CompareAlgorithms:
        this->CompareAlgorithms();
        break;
      case MenuChoice::Quit:
        break;
    }
    
    if (variant != MenuChoice::Quit) {
      std::cout << "Press Enter to continue" << std::endl;
      std::cin.get();
    }
  } while (variant != MenuChoice::Quit);
}

void Menu::PrintMenu() {
  std::cout << "Enter the number of the selected menu item." << std::endl;
  std::cout << "1: Loading the original graph from a file." << std::endl;
  std::cout << "2: Graph traversal in breadth with output of the result to the "
               "console."
            << std::endl;
  std::cout
      << "3: Graph traversal in depth with output of the result to the console."
      << std::endl;
  std::cout << "4: Searching for the shortest path between any two vertices "
               "and displaying the result to the console."
            << std::endl;
  std::cout
      << "5: Searching for the shortest paths between all pairs of vertices in "
         "the graph with the output of the resulting matrix to the console."
      << std::endl;
  std::cout << "6: Searching for the minimal spanning tree in the graph with "
               "the output of the resulting adjacency matrix to the console."
            << std::endl;
  std::cout << "7: Solving the salesman problem with the output of the "
               "resulting route and its length to the console."
            << std::endl;
  std::cout << "8: Compare ant algorithm, with the annealing and brute force algorithms."
          << std::endl;
  std::cout << "0: Quit" << std::endl;
  std::cout << ">";
}

int Menu::GetVariant(int min, int max) {
  int variant;
  std::string str;  // строка для считывания введённых данных
  std::getline(std::cin, str);  // считываем строку
  // пока ввод некорректен, сообщаем об этом и просим повторить его
  while (sscanf(str.c_str(), "%d", &variant) != 1 || variant > max || variant < min) {
    std::cout << "Incorrect input. Try again: ";  // выводим сообщение об ошибке
    std::getline(std::cin, str);  // считываем строку повторно
  }
  return variant;
}

void Menu::LoadGraphFromFile() {
  try {
    std::string filename;
    std::cout << "Input filename: ";
    getline(std::cin, filename);
    graph_.reset(new Graph(filename));
  } catch (const std::exception &err) {
    std::cout << "Load error: " << err.what() << std::endl;
  }
}

void Menu::BreadthFirstSearch() {
  Graph *graph = GetGraph();
  if(!graph) {
    std::cout << "Error: load a graph from a file first" << std::endl;
    return;
  }
  std::cout << "Input starting index: " << std::endl;
  int n = GetVariant(1, static_cast<int>(graph->Size()));
  auto breadth_path = graph_algrthm_.BreadthFirstSearch(*graph, n);
  std::cout << "Path: ";
  std::size_t size = breadth_path.size();
  for (std::size_t i = 0; i < size; i++) {
    std::cout << breadth_path[i];
    if (i != size - 1)
      std::cout << "->";
  }
  std::cout << std::endl;
}

void Menu::DepthFirstSearch() {
  Graph *graph = GetGraph();
  if(!graph) {
    std::cout << "Error: load a graph from a file first" << std::endl;
    return;
  }
  std::cout << "Input starting index: " << std::endl;
  int n = GetVariant(1, static_cast<int>(graph->Size()));
  auto depth_path = graph_algrthm_.DepthFirstSearch(*graph, n);
  std::cout << "Path: ";
  SeparatedContainerPrint(depth_path.begin(), depth_path.end(), "->");
  std::cout << std::endl;
}

void Menu::CompareAlgorithms() {
  Graph *graph = GetGraph();
  if(!graph) {
    std::cout << "Error: load a graph from a file first" << std::endl;
    return;
  }
  std::cout << "Input number of operations(n): " << std::endl;
  int n = GetVariant(1, std::numeric_limits<int>::max());
  std::cout << std::left << std::setw(25) << "Ant algorithm: ";
  auto ant_fp = std::bind(&Menu::SolveTravelingSalesmanProblem, this, std::placeholders::_1, std::placeholders::_2);
  MeasureTSMAlgorithmTime(ant_fp, TSMSolutionType::Ant, static_cast<std::size_t>(n));
  std::cout << std::left << std::setw(25) << "Annealing algorithm: ";
  auto ann_fp = std::bind(&Menu::SolveTravelingSalesmanProblem, this, std::placeholders::_1, std::placeholders::_2);
  MeasureTSMAlgorithmTime(ann_fp, TSMSolutionType::Annealing, static_cast<std::size_t>(n));
  std::cout << std::left << std::setw(25) << "Brute force algorithm: ";
  auto brute_fp = std::bind(&Menu::SolveTravelingSalesmanProblem, this, std::placeholders::_1, std::placeholders::_2);
  MeasureTSMAlgorithmTime(brute_fp, TSMSolutionType::Brute, static_cast<std::size_t>(n));
}

void Menu::MeasureTSMAlgorithmTime(std::function<void(TSMSolutionType, bool)> func, TSMSolutionType type, std::size_t n) {
  auto start = std::chrono::steady_clock::now();
  for (std::size_t i = 0; i < n; ++i) {
    func(type, false);
  }
  auto end = std::chrono::steady_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    << " ms" << std::endl;
}

void Menu::ShortestPathBetweenTwoVertices() {
  Graph *graph = GetGraph();
  if(!graph) {
    std::cout << "Error: load a graph from a file first";
    return;
  }
  std::cout << "vertex1: ";
  int vertex1 = this->GetVariant(1, static_cast<int>(graph->Size()));
  std::cout << "vertex2: ";
  int vertex2 = this->GetVariant(1, static_cast<int>(graph->Size()));
  double result = graph_algrthm_.getShortestPathBetweenVertices(*graph, vertex1, vertex2);
  std::cout << result << std::endl;
}

void Menu::ShortestPathsBetweenAllVertices() {
  Graph *graph = GetGraph();
  if(!graph) {
    std::cout << "Error: load a graph from a file first";
    return;
  }
  std::vector<std::vector<double>> result =
      graph_algrthm_.getShortestPathsBetweenAllVertices(*graph);
  std::size_t size = graph->Size();
  for (std::size_t i = 0; i < size; i++) {
    for (std::size_t j = 0; j < size; j++) {
      std::cout << std::setw(5) << result[i][j];
    }
    std::cout << std::endl;
  }
}

void Menu::LeastSpanningTree() {
  Graph *graph = GetGraph();
  if(!graph) {
    std::cout << "Error: load a graph from a file first";
    return;
  }
  std::size_t size = graph->Size();
  Graph result(size);
  result = graph_algrthm_.getLeastSpanningTree(*graph);
  for (std::size_t i = 0; i < size; i++) {
    for (std::size_t j = 0; j < size; j++) {
      std::cout << std::setw(5) << result(i, j);
    }
    std::cout << std::endl;
  }
}

void Menu::SolveTravelingSalesmanProblem(TSMSolutionType al_type, bool show_result) { 
  Graph *graph = GetGraph();
  if(!graph) {
    std::cout << "Error: load a graph from a file first" << std::endl;
    return;
  }
  s21::TsmResult result;
  if (al_type == TSMSolutionType::Ant)
    result = graph_algrthm_.solveTravelingSalesmanProblem(*graph);
  else if (al_type == TSMSolutionType::Annealing)
    result = graph_algrthm_.SimulatedAnnealint(*graph);
  else if (al_type == TSMSolutionType::Brute)
    result = graph_algrthm_.BruteForceAlg(*graph);
  if (show_result) {
    if (al_type == TSMSolutionType::Ant)
      std::cout << "Ant algorithm:" << std::endl;
    else if (al_type == TSMSolutionType::Annealing)
      std::cout << "Annealing algorithm:" << std::endl;
    else if (al_type == TSMSolutionType::Brute)
      std::cout << "Brute force algorithm:" << std::endl;
    std::cout << "Distance: " << result.distance << std::endl;
    std::cout << "Path: ";
    SeparatedContainerPrint(result.vertices.begin(), result.vertices.end(), "->");
    std::cout << std::endl;
  }
}
}  // namespace s21
