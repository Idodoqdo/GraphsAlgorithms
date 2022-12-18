// Copyright <lwolmer, lshiela, jgerrick> 2022
#include "menu.h"

namespace s21 {
void Menu::Start() {
  std::size_t variant;  // выбранный пункт меню
  Graph graph(2);
  GraphAlgorithms alg;
  do {
    this->PrintMenu();  // выводим меню на экран
    variant = this->GetVariant(Quit);  // получаем номер выбранного пункта меню
    switch (variant) {
      case kLoadGraphFromFile:
        this->LoadGraphFromFile(graph);
        break;
      case kBreadthFirstSearch:
        this->BreadthFirstSearch();
        break;
      case kDepthFirstSearch:
        this->DepthFirstSearch();
        break;
      case kShortestPathBetweenTwoVertices:
        this->ShortestPathBetweenTwoVertices(graph, alg);
        break;
      case kShortestPathsBetweenAllVertices:
        this->ShortestPathsBetweenAllVertices(graph, alg);
        break;
      case kLeastSpanningTree:
        this->LeastSpanningTree(graph, alg);
        break;
      case kSolveTravelingSalesmanProblem:
        this->SolveTravelingSalesmanProblem();
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
  std::cout << "8: Quit" << std::endl;
  std::cout << ">";
}

std::size_t Menu::GetVariant(std::size_t capacity) {
  std::size_t variant;
  std::string str;  // строка для считывания введённых данных
  std::getline(std::cin, str);  // считываем строку
  // пока ввод некорректен, сообщаем об этом и просим повторить его
  while (sscanf(str.c_str(), "%lu", &variant) != 1 || variant < 1 ||
         variant > capacity) {
    std::cout << "Incorrect input. Try again: ";  // выводим сообщение об ошибке
    std::getline(std::cin, str);  // считываем строку повторно
  }
  return variant;
}

void Menu::LoadGraphFromFile(Graph &graph) {
  try {
    std::string filename;
    std::cout << "Input filename: ";
    getline(std::cin, filename);
    graph.LoadGraphFromFile(filename);
  } catch (const std::exception &err) {
    std::cout << "Load error: " << err.what() << std::endl;
  }
}

void Menu::BreadthFirstSearch() { std::cout << "ToDo" << std::endl; }

void Menu::DepthFirstSearch() { std::cout << "ToDo" << std::endl; }

void Menu::ShortestPathBetweenTwoVertices(Graph &graph, GraphAlgorithms &alg) {
  std::cout << "vertex1: ";
  int vertex1 = static_cast<int>(this->GetVariant(graph.Size()));
  std::cout << "vertex2: ";
  int vertex2 = static_cast<int>(this->GetVariant(graph.Size()));
  double result = alg.getShortestPathBetweenVertices(graph, vertex1, vertex2);
  std::cout << result << std::endl;
}

void Menu::ShortestPathsBetweenAllVertices(Graph &graph, GraphAlgorithms &alg) {
  std::vector<std::vector<double>> result =
      alg.getShortestPathsBetweenAllVertices(graph);
  std::size_t size = graph.Size();
  for (std::size_t i = 0; i < size; i++) {
    for (std::size_t j = 0; j < size; j++) {
      std::cout << std::setw(5) << result[i][j];
    }
    std::cout << std::endl;
  }
}

void Menu::LeastSpanningTree(Graph &graph, GraphAlgorithms &alg) {
  std::size_t size = graph.Size();
  Graph result(size);
  result = alg.getLeastSpanningTree(graph);
  for (std::size_t i = 0; i < size; i++) {
    for (std::size_t j = 0; j < size; j++) {
      std::cout << std::setw(5) << graph(i, j);
    }
    std::cout << std::endl;
  }
}

void Menu::SolveTravelingSalesmanProblem() { std::cout << "ToDo" << std::endl; }
}  // namespace s21
