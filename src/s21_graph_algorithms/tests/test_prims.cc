#include <gtest/gtest.h>

#include "s21_graph_algorithms.h"

TEST(prims, test_1) {
  int graph5x5[] = {0, 9, 75, 0, 0,
                    9, 0, 95, 19, 42,
                    75, 95, 0, 51, 66,
                    0,  19, 51, 0, 31,
                    0,  42, 66, 31, 0};
  s21::Graph graph(graph5x5, 5);
  s21::Graph result(5);
  s21::GraphAlgorithms graph_algorithms;
  result = graph_algorithms.getLeastSpanningTree(graph);
  ASSERT_TRUE(result(1, 2) == 9);
  ASSERT_TRUE(result(2, 4) == 19);
  ASSERT_TRUE(result(4, 5) == 31);
  ASSERT_TRUE(result(4, 3) == 51);
}

TEST(prims, test_2) {
  int graph5x5[] = {0, 2, 0, 6, 0,
                    2, 0, 3, 8, 5,
                    0, 3, 0, 0, 7,
                    6, 8, 0, 0, 9,
                    0, 5, 7, 9, 0};
  s21::Graph graph(graph5x5, 5);
  s21::Graph result(5);
  s21::GraphAlgorithms graph_algorithms;
  result = graph_algorithms.getLeastSpanningTree(graph);
  ASSERT_TRUE(result(1, 2) == 2);
  ASSERT_TRUE(result(2, 3) == 3);
  ASSERT_TRUE(result(2, 5) == 5);
  ASSERT_TRUE(result(1, 4) == 6);
}
