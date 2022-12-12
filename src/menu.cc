#include "menu.h"

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
  std::cout << "9: Quit" << std::endl;
  std::cout << ">";
}

int Menu::GetVariant(int capacity) {
  int variant;
  std::string str;  // строка для считывания введённых данных
  std::getline(std::cin, str);  // считываем строку
  // пока ввод некорректен, сообщаем об этом и просим повторить его
  while (sscanf(str.c_str(), "%d", &variant) != 1 || variant < 1 ||
         variant >= capacity) {
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
    graph_.LoadGraphFromFile(filename);
  } catch (const std::exception& err) {
    std::cout << "Load error: " << err.what() << std::endl;
    throw;
  }
}

void Menu::BreadthFirstSearch() { std::cout << "ToDo" << std::endl; }

void Menu::DepthFirstSearch() { std::cout << "ToDo" << std::endl; }

void Menu::ShortestPathBetweenTwoVertices() {
  s21::GraphAlgorithms alg;
  Menu tmp;
  std::cout << "vertex1>";
  int vertex1 = tmp.GetVariant(graph_.Size());
  std::cout << "vertex2>";
  int vertex2 = tmp.GetVariant(graph_.Size());
  int result = alg.getShortestPathBetweenVertices(graph_, vertex1, vertex2);
  std::cout << result;
}

void Menu::ShortestPathsBetweenAllVertices() {
  s21::GraphAlgorithms alg;
  // char str[32];
  std::vector<std::vector<double>> result =
      alg.getShortestPathsBetweenAllVertices(graph_);
  std::size_t size = graph_.Size();
  for (std::size_t i = 0; i < size; i++) {
    for (std::size_t j = 0; j < size; j++) {
      // sprintf(str, " %5lf", result[i][j]); // для красивого вывода с ровными столбиками
      std::cout << result[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void Menu::LeastSpanningTree() {
  s21::GraphAlgorithms alg;
  // char str[32];
  std::size_t size = graph_.Size();
  s21::Graph result(size);
  result = alg.getLeastSpanningTree(graph_);
  for (std::size_t i = 0; i < size; i++) {
    for (std::size_t j = 0; j < size; j++) {
      // sprintf(str, " %5lf", graph_(i, j)); // для красивого вывода с ровными столбиками
      std::cout << graph_(i, j) << " ";
    }
    std::cout << std::endl;
  }
}

void Menu::SolveTravelingSalesmanProblem() { std::cout << "ToDo" << std::endl; }
