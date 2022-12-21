// Copyright <lwolmer, lshiela, jgerrick> 2022
#include <gtest/gtest.h>
#include "s21_graph.h"

TEST(graph_misc, connected_nodes_fork) {
  double graph_raw[] = {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0};
  s21::Graph graph(graph_raw, 4);
  auto paths_1 = graph.GetConnectedNodes(1);
  EXPECT_EQ(paths_1.size(), 1);
  EXPECT_EQ(paths_1[0], 3);
  auto paths_3 = graph.GetConnectedNodes(3);
  std::size_t connected_nodes[] = {0, 1, 2};
  EXPECT_EQ(paths_3.size(), 3);
  for (std::size_t i = 0; i < paths_3.size(); i++) {
    EXPECT_EQ(paths_3[i], connected_nodes[i]);
  }
}

TEST(graph_misc, connected_nodes_cycled) {
  double graph_raw[] = {0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0};
  s21::Graph graph(graph_raw, 4);
  auto paths_1 = graph.GetConnectedNodes(1);
  EXPECT_EQ(paths_1.size(), 2);
  std::size_t connected_nodes[] = {0, 2};
  for (std::size_t i = 0; i < paths_1.size(); i++) {
    EXPECT_EQ(paths_1[i], connected_nodes[i]);
  }
  auto paths_3 = graph.GetConnectedNodes(3);
  EXPECT_EQ(paths_3.size(), 2);
  for (std::size_t i = 0; i < paths_3.size(); i++) {
    EXPECT_EQ(paths_3[i], connected_nodes[i]);
  }
}

TEST(graph_misc, connected_nodes_crisscross) {
  double graph_raw[] = {0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0};
  s21::Graph graph(graph_raw, 4);
  auto paths_0 = graph.GetConnectedNodes(0);
  std::size_t connected_nodes[] = {2, 3};
  EXPECT_EQ(paths_0.size(), 2);
  for (std::size_t i = 0; i < paths_0.size(); i++) {
    EXPECT_EQ(paths_0[i], connected_nodes[i]);
  }
  auto paths_2 = graph.GetConnectedNodes(2);
  std::size_t connected_nodes_2[] = {0, 1};
  EXPECT_EQ(paths_2.size(), 2);
  for (std::size_t i = 0; i < paths_2.size(); i++) {
    EXPECT_EQ(paths_2[i], connected_nodes_2[i]);
  }
}
