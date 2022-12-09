#include <gtest/gtest.h>

#include "../s21_graph_algorithms.h"

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
  ASSERT_EQ(result(0, 1), 9);
  ASSERT_EQ(result(1, 3), 19);
  ASSERT_EQ(result(3, 4), 31);
  ASSERT_EQ(result(3, 2), 51);
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
  ASSERT_EQ(result(0, 1), 2);
  ASSERT_EQ(result(1, 2), 3);
  ASSERT_EQ(result(1, 4), 5);
  ASSERT_EQ(result(0, 3), 6);
}
