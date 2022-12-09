#include <gtest/gtest.h>
#include "s21_graph_algorithms.h"
#include "config.h"

TEST(graph_algorithms, Ant) {
  s21::TsmResult result{};
  s21::Graph graph(CMAKE_CURRENT_SOURCE_DIR"/graph_raw_file");
  s21::GraphAlgorithms testAlg;
  result = testAlg.solveTravelingSalesmanProblem(graph);
  EXPECT_EQ(result.distance, 253);
}