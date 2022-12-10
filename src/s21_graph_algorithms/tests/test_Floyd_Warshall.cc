#include <gtest/gtest.h>

#include "../s21_graph_algorithms.h"

TEST(Floyd_Warshall, test_1) {
  double graph4x4[] = {0, 5, 0, 10,
                       0, 0, 3, 0,
                       0, 0, 0, 1,
                       0, 0, 0, 0};
  s21::Graph graph(graph4x4, 4);
  s21::Graph result(4);
  s21::GraphAlgorithms graph_algorithms;
  result = graph_algorithms.getShortestPathsBetweenAllVertices(graph);
  ASSERT_EQ(result(3, 0), 9);
  ASSERT_EQ(result(2, 0), 8);
  ASSERT_EQ(result(1, 0), 5);
  ASSERT_EQ(result(3, 1), 4);
  ASSERT_EQ(result(2, 1), 3);
  ASSERT_EQ(result(3, 2), 1);
}

TEST(Floyd_Warshall, test_2) {
  double graph4x4[] = {0, 3, 0, 7,
                       8, 0, 2, 0,
                       5, 0, 0, 1,
                       2, 0, 0, 0};
  s21::Graph graph(graph4x4, 4);
  s21::Graph result(4);
  s21::GraphAlgorithms graph_algorithms;
  result = graph_algorithms.getShortestPathsBetweenAllVertices(graph);
  ASSERT_EQ(result(3, 1), 3);
  ASSERT_EQ(result(2, 0), 5);
  ASSERT_EQ(result(2, 3), 7);
}