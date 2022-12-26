// Copyright <lwolmer, lshiela, jgerrick> 2022
#include <gtest/gtest.h>
#include "config.h"
#include "s21_graph_algorithms.h"

TEST(graph_algorithms, Ant) {
  s21::TsmResult result{};
  s21::Graph graph(CMAKE_CURRENT_SOURCE_DIR "/graph_raw_file");
  s21::GraphAlgorithms testAlg;
  result = testAlg.solveTravelingSalesmanProblem(graph);
  EXPECT_LE(result.distance, 300);
}

TEST(graph_algorithms, Ant2) {
  s21::TsmResult result{};
  double matrix[] = {0,  10, 15, 20, 10, 0,  35, 25,
                     15, 35, 0,  30, 20, 25, 30, 0};
  s21::Graph graph(matrix, 4);
  s21::GraphAlgorithms testAlg;
  result = testAlg.solveTravelingSalesmanProblem(graph);
  EXPECT_EQ(result.distance, 80);
}

TEST(graph_algorithms, simulated_annealing) {
  s21::TsmResult result{};
  s21::Graph graph(CMAKE_CURRENT_SOURCE_DIR "/graph_raw_file");
  s21::GraphAlgorithms testAlg;
  result = testAlg.SimulatedAnnealint(graph);
  EXPECT_LE(result.distance, 300);
}

TEST(graph_algorithms, simulated_annealing_2) {
  s21::TsmResult result{};
  double matrix[] = {0,  10, 15, 20, 10, 0,  35, 25,
                     15, 35, 0,  30, 20, 25, 30, 0};
  s21::Graph graph(matrix, 4);
  s21::GraphAlgorithms testAlg;
  result = testAlg.SimulatedAnnealint(graph);
  EXPECT_EQ(result.distance, 80);
}

TEST(graph_algorithms, brute_force) {
  s21::TsmResult result{};
  s21::Graph graph(CMAKE_CURRENT_SOURCE_DIR "/graph_raw_file");
  s21::GraphAlgorithms testAlg;
  result = testAlg.BruteForceAlg(graph);
  EXPECT_EQ(result.distance, 253);
}

TEST(graph_algorithms, simulated_annealing_3) {
  s21::TsmResult result{};
  double matrix[] = {0, 10, 0, 7, 0, 10, 0, 15, 0, 0, 0, 15, 0,
                     0, 3,  7, 0, 0, 0,  8, 0,  0, 3, 8, 0};
  s21::Graph graph(matrix, 5);
  s21::GraphAlgorithms testAlg;
  result = testAlg.SimulatedAnnealint(graph);
  EXPECT_EQ(result.distance, 43);
}

TEST(graph_algorithms, Ant3) {
  s21::TsmResult result{};
  double matrix[] = {0, 10, 0, 7, 0, 10, 0, 15, 0, 0, 0, 15, 0,
                     0, 3,  7, 0, 0, 0,  8, 0,  0, 3, 8, 0};
  s21::Graph graph(matrix, 5);
  s21::GraphAlgorithms testAlg;
  result = testAlg.solveTravelingSalesmanProblem(graph);
  EXPECT_EQ(result.distance, 43);
}
