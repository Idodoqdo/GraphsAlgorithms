// Copyright <lwolmer, lshiela, jgerrick> 2022
#include "s21_graph.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <regex>
#include <limits>

namespace s21 {
Graph::Graph(const std::string &filepath) {
  LoadGraphFromFile(filepath);
}

Graph::Graph(std::size_t size) {
  AllocateMatrix(size);
}

Graph::Graph(double *matrix, std::size_t size) : Graph(size) {
  for(std::size_t y = 0; y < size; y++) {
    for(std::size_t x = 0; x < size; x++) {
      this->operator()(x, y) = matrix[x + size * y];
    }
  }
}

void Graph::AllocateMatrix(std::size_t size) {
  matrix_.resize(size);
  for (std::size_t i = 0; i < size; i++) {
    matrix_[i].resize(size, 0);
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

std::vector<std::size_t> Graph::GetConnectedNodes(std::size_t index) {
  std::size_t size = Size();
  std::vector<std::size_t> paths;
  for (std::size_t x = 0; x < size; x++) {
    if (x == index)
      continue;
    if (this->operator()(x, index) > std::numeric_limits<double>::epsilon())
      paths.push_back(x);
  }
  return paths;
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
      AllocateMatrix(size);
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
  } else {
    throw std::runtime_error("The file does not exist.");
  }
}

std::multimap<double, std::pair<std::size_t, std::size_t>> Graph::GetAllPathsSortedByWeight() const {
  std::multimap<double, std::pair<std::size_t, std::size_t>> ms;
  std::size_t size = Size();
  for (std::size_t y = 0; y < size; y++) {
    for (std::size_t x = 0; x < y; x++) {
      double weight = this->operator()(x, y);
      if (weight > std::numeric_limits<double>::epsilon()) {
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
    file << "graph {\n";
    auto ms_sorted = GetAllPathsSortedByWeight();
    for (auto i(ms_sorted.begin()), end(ms_sorted.end());  i != end; i++) {
      file << "\t" << i->second.first + 1 << " -- " << i->second.second + 1 << "\n";
    }
          
    file << "}";
  }
  file.close();
}
} // namespace s21
