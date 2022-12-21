// Copyright <lwolmer, lshiela, jgerrick> 2022
#include <gtest/gtest.h>

#include "s21_graph_algorithms.h"

TEST(dijkstra, test_1) {
  double graph6x6[] = {0, 7,  9, 0,  0, 14, 7,  0,  10, 15, 0, 0,
                       9, 10, 0, 11, 0, 2,  0,  15, 11, 0,  6, 0,
                       0, 0,  0, 6,  0, 9,  14, 0,  2,  0,  9, 0};
  s21::Graph graph(graph6x6, 6);
  s21::GraphAlgorithms graph_algorithms;
  double result = graph_algorithms.getShortestPathBetweenVertices(graph, 1, 6);
  ASSERT_EQ(result, 11);
}

TEST(dijkstra, test_2) {
  double graph9x9[] = {0, 4, 0, 0, 0, 0, 0, 8,  0, 4, 0, 8, 0, 0,  0,  0,  11,
                       0, 0, 8, 0, 7, 0, 4, 0,  0, 2, 0, 0, 7, 0,  9,  14, 0,
                       0, 0, 0, 0, 0, 9, 0, 10, 0, 0, 0, 0, 0, 4,  14, 10, 0,
                       2, 0, 0, 0, 0, 0, 0, 0,  2, 0, 1, 6, 8, 11, 0,  0,  0,
                       0, 1, 0, 7, 0, 0, 2, 0,  0, 0, 6, 7, 0};
  s21::Graph graph(graph9x9, 9);
  s21::GraphAlgorithms graph_algorithms;
  double result = graph_algorithms.getShortestPathBetweenVertices(graph, 1, 5);
  ASSERT_EQ(result, 21);
}
