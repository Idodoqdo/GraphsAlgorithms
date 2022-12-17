// Copyright <lwolmer, lshiela, jgerrick> 2022
#include <gtest/gtest.h>
#include "s21_graph_algorithms.h"

TEST(graph_search_depth, fork) {
  double graph_raw[] = {0, 0, 0, 1,
                      0, 0, 0, 1,
                      0, 0, 0 ,1,
                      1, 1, 1, 0};
  s21::Graph graph(graph_raw, 4);
  s21::GraphAlgorithms graph_algorithms;
  auto depth_path = graph_algorithms.DepthFirstSearch(graph, 1);
  std::size_t path[] = {1, 4, 2, 3};
  EXPECT_EQ(depth_path.size(), 4);
  for (std::size_t i = 0; i < depth_path.size(); i++) {
    EXPECT_EQ(depth_path[i], path[i]);
  }
}

TEST(graph_search_depth, geeks_example) {
  double graph_raw[] = {0, 1, 1, 1, 1,
                        1, 0, 0, 0, 0,
                        1, 0, 0, 0, 0,
                        1, 0, 0, 0, 0,
                        1, 0, 0, 0, 0};
  s21::Graph graph(graph_raw, 5);
  s21::GraphAlgorithms graph_algorithms;
  auto depth_path = graph_algorithms.DepthFirstSearch(graph, 1);
  std::size_t path[] = {1, 2, 3, 4, 5};
  EXPECT_EQ(depth_path.size(), 5);
  for (std::size_t i = 0; i < depth_path.size(); i++) {
    EXPECT_EQ(depth_path[i], path[i]);
  }
}

TEST(graph_search_depth, geeks_example2) {
  double graph_raw[] = {0, 1, 1, 0, 0,
                        1, 0, 0, 1, 0,
                        1, 0, 0, 0, 0,
                        0, 1, 0, 0, 0,
                        0, 0, 0, 0, 0};
  s21::Graph graph(graph_raw, 5);
  s21::GraphAlgorithms graph_algorithms;
  auto depth_path = graph_algorithms.DepthFirstSearch(graph, 1);
  std::size_t path[] = {1, 2, 4, 3};
  EXPECT_EQ(depth_path.size(), 4);
  for (std::size_t i = 0; i < depth_path.size(); i++) {
    EXPECT_EQ(depth_path[i], path[i]);
  }
}

TEST(graph_search_depth, not_connected) {
  double graph_raw[] = {0, 0, 1, 0,
                      0, 0, 0, 1,
                      1, 0, 0 ,0,
                      0, 1, 0, 0};
  s21::Graph graph(graph_raw, 4);
  s21::GraphAlgorithms graph_algorithms;
  auto depth_path = graph_algorithms.DepthFirstSearch(graph, 1);
  std::size_t path[] = {1, 3};
  EXPECT_EQ(depth_path.size(), 2);
  for (std::size_t i = 0; i < depth_path.size(); i++) {
    EXPECT_EQ(depth_path[i], path[i]);
  }
}