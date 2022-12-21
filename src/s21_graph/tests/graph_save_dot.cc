// Copyright <lwolmer, lshiela, jgerrick> 2022

#include <gtest/gtest.h>
#include <sys/stat.h>
#include "config.h"
#include "s21_graph.h"

static inline bool FileExists(const std::string& name) {
  struct stat buffer;
  return (stat(name.c_str(), &buffer) == 0);
}

TEST(graph, dot_to_file) {
  s21::Graph graph(CMAKE_CURRENT_SOURCE_DIR "/graph_raw_file");
  graph.ExportGraphToDot(CMAKE_CURRENT_SOURCE_DIR "/test.dot");
  EXPECT_TRUE(FileExists(CMAKE_CURRENT_SOURCE_DIR "/test.dot"));
}

TEST(graph, dot_to_file_fork) {
  double graph_raw[] = {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0};
  s21::Graph graph(graph_raw, 4);
  graph.ExportGraphToDot(CMAKE_CURRENT_SOURCE_DIR "/test_fork.dot");
  EXPECT_TRUE(FileExists(CMAKE_CURRENT_SOURCE_DIR "/test_fork.dot"));
}

TEST(graph, dot_to_file_cycled) {
  double graph_raw[] = {0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0};
  s21::Graph graph(graph_raw, 4);
  graph.ExportGraphToDot(CMAKE_CURRENT_SOURCE_DIR "/test_cycled.dot");
  EXPECT_TRUE(FileExists(CMAKE_CURRENT_SOURCE_DIR "/test_cycled.dot"));
}

TEST(graph, dot_to_file_intersect) {
  double graph_raw[] = {0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0};
  s21::Graph graph(graph_raw, 4);
  graph.ExportGraphToDot(CMAKE_CURRENT_SOURCE_DIR "/test_intersect.dot");
  EXPECT_TRUE(FileExists(CMAKE_CURRENT_SOURCE_DIR "/test_intersect.dot"));
}

TEST(graph, dot_to_file_no_connection) {
  double graph_raw[] = {0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0};
  s21::Graph graph(graph_raw, 4);
  graph.ExportGraphToDot(CMAKE_CURRENT_SOURCE_DIR "/test_no_connection.dot");
  EXPECT_TRUE(FileExists(CMAKE_CURRENT_SOURCE_DIR "/test_no_connection.dot"));
}

TEST(graph, dot_to_file_crisscross) {
  double graph_raw[] = {0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0};
  s21::Graph graph(graph_raw, 4);
  graph.ExportGraphToDot(CMAKE_CURRENT_SOURCE_DIR "/test_crisscross.dot");
  EXPECT_TRUE(FileExists(CMAKE_CURRENT_SOURCE_DIR "/test_crisscross.dot"));
}

TEST(graph, dot_to_file_tree) {
  double graph_raw[] = {0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0,
                        0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0};
  s21::Graph graph(graph_raw, 5);
  graph.ExportGraphToDot(CMAKE_CURRENT_SOURCE_DIR "/test_tree.dot");
  EXPECT_TRUE(FileExists(CMAKE_CURRENT_SOURCE_DIR "/test_tree.dot"));
}