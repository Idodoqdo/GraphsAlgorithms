// Copyright <lwolmer, lshiela, jgerrick> 2022
#include "s21_graph.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <regex>

namespace s21 {
Graph::Graph(const std::string &filepath) {
  LoadGraphFromFile(filepath);
}

Graph::Graph(int size) {
  AllocateMatrix(size);
}

Graph::Graph(int *matrix, int size) : Graph(size) {
  for(int y = 0; y < size; y++) {
    for(int x = 0; x < size; x++) {
      this->operator()(x, y) = matrix[x + size * y];
    }
  }
}

void Graph::AllocateMatrix(int size) {
  assert(size >= 2);
  std::size_t ssize = static_cast<std::size_t>(size);
  matrix_.resize(ssize);
  for (std::size_t i = 0; i < ssize; i++) {
    matrix_[i].resize(ssize, 0);
  }
}

bool Graph::CheckFormat(std::ifstream &stream, std::string reg) const {
  std::regex r(reg);
  std::string line;
  std::streampos pos = stream.tellg();
  getline(stream, line);
  bool result = std::regex_match(line, r);
  stream.seekg(pos);
  return result;
}

void Graph::LoadGraphFromFile(const std::string &filename) {
  std::ifstream file(filename);
  if (file.is_open()) {
    try {
      if (!CheckFormat(file, "^[1-9][0-9]*$"))
        throw std::runtime_error("Bad format");
      std::size_t size;
      file >> size;
      file.ignore(1);
      AllocateMatrix(static_cast<int>(size));
      std::size_t line_num = 0;
      while(!file.eof()) {
        if (!CheckFormat(file, "^([0-9]+ +){" + std::to_string(size - 1) + "}[0-9]+$"))
          throw std::runtime_error("Bad format");
        for(std::size_t i = 0; i < size; i++) {
          file >> matrix_[line_num][i];
        }
        line_num++;
        file.ignore(1);
      }
      if (line_num != size)
        throw std::runtime_error("Bad format");
    } catch(const std::exception& e) {
      file.close();
      throw;
    }
    file.close();
  }
}

std::multimap<int, std::pair<int, int>> Graph::GetAllPathsSortedByWeight() const {
  std::multimap<int, std::pair<int, int>> ms;
  int size = Size();
  for (int y = 0; y < size; y++) {
    for (int x = 0; x < y; x++) {
      int weight = this->operator()(x, y);
      if (weight) {
        ms.insert({weight, std::make_pair(x, y)});
      }
    }
  }
  return ms;
}

void Graph::ExportGraphToDot(const std::string& filename) const {
  std::ofstream file;
  file.open (filename);
  if (file.is_open()) {
    file << "digraph graphname {\n";
    file << "\tedge [arrowhead=none];\n";
    auto ms_sorted = GetAllPathsSortedByWeight();
    for (auto i(ms_sorted.begin()), end(ms_sorted.end());  i != end; i++) {
      file << "\t" << i->second.first + 1 << " -> " << i->second.second + 1 << "\n";
    }
          
    file << "}";
  }
  file.close();
}
} // namespace s21