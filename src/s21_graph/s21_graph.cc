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

Graph::Graph(size_t size) {
  AllocateMatrix(size);
}

Graph::Graph(double *matrix, size_t size) : Graph(size) {
  for(size_t y = 0; y < size; y++) {
    for(size_t x = 0; x < size; x++) {
      this->operator()(x, y) = matrix[x + size * y];
    }
  }
}

void Graph::AllocateMatrix(size_t size) {
  assert(size >= 2);
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
  }
}

void Graph::ExportGraphToDot(std::string filename) {
  std::cout << filename;
}
} // namespace s21
