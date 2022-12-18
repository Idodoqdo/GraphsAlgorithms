// Copyright <lwolmer, lshiela, jgerrick> 2022
#include "menu.h"
#include <chrono>

namespace s21 {
void Menu::Start() {
  int variant;  // выбранный пункт меню
  do {
    this->PrintMenu();  // выводим меню на экран
    variant = this->GetVariant(0, kCompareAlgorithms);  // получаем номер выбранного пункта меню
    switch (variant) {
      case kLoadGraphFromFile:
        this->LoadGraphFromFile();
        break;
      case kBreadthFirstSearch:
        this->BreadthFirstSearch();
        break;
      case kDepthFirstSearch:
        this->DepthFirstSearch();
        break;
      case kShortestPathBetweenTwoVertices:
        this->ShortestPathBetweenTwoVertices();
        break;
      case kShortestPathsBetweenAllVertices:
        this->ShortestPathsBetweenAllVertices();
        break;
      case kLeastSpanningTree:
        this->LeastSpanningTree();
        break;
      case kSolveTravelingSalesmanProblem:
        this->SolveTravelingSalesmanProblem(TSMSolutionType::Annealing);
        break;
      case kCompareAlgorithms:
        this->CompareAlgorithms();
        break;
    }
    
    if (variant != Quit) {
      std::cout << "Press Enter to continue" << std::endl;
      std::cin.get();
    }
  } while (variant != Quit);
}

void Menu::PrintMenu() {
  std::cout << "Enter the number of the selected menu item." << std::endl;
  std::cout << "1: loading the original graph from a file." << std::endl;
  std::cout << "2: graph traversal in breadth with output of the result to the "
               "console."
            << std::endl;
  std::cout
      << "3: graph traversal in depth with output of the result to the console."
      << std::endl;
  std::cout << "4: searching for the shortest path between any two vertices "
               "and displaying the result to the console."
            << std::endl;
  std::cout
      << "5: searching for the shortest paths between all pairs of vertices in "
         "the graph with the output of the resulting matrix to the console."
      << std::endl;
  std::cout << "6: searching for the minimal spanning tree in the graph with "
               "the output of the resulting adjacency matrix to the console."
            << std::endl;
  std::cout << "7: solving the salesman problem with the output of the "
               "resulting route and its length to the console."
            << std::endl;
  std::cout << "8: Compare ant algorithm, with the others."
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
  std::size_t size = depth_path.size();
  std::cout << "Path: ";
  for (std::size_t i = 0; i < size; i++) {
    std::cout << depth_path[i];
    if (i != size - 1)
      std::cout << "->";
  }
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
      std::cout << std::setw(5) << graph->operator()(i, j);
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
  if (show_result) {
    if (al_type == TSMSolutionType::Ant)
      std::cout << "Ant algorithm:" << std::endl;
    else if (al_type == TSMSolutionType::Annealing)
      std::cout << "Annealing algorithm:" << std::endl;
    std::cout << "Distance: " << result.distance << std::endl;
    std::cout << "Path: ";
    std::size_t size = result.vertices.size();
    for (std::size_t i = 0; i < size; i++) {
      std::cout <<result.vertices[i];
      if (i != size - 1)
        std::cout << "->";
    }
    std::cout << std::endl;
  }
}
}  // namespace s21
