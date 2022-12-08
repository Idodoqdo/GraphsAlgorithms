// Copyright <lwolmer, lshiela, jgerrick> 2022

#include <gtest/gtest.h>
#include "s21_graph.h"
#include "config.h"

TEST(graph, constructor_dimesnsions) {
  ASSERT_DEATH(s21::Graph graph_e1(-10), ".*Assertion.*failed.*");
  ASSERT_DEATH(s21::Graph graph_e2(0), ".*Assertion.*failed.*");
  ASSERT_DEATH(s21::Graph graph_e3(1), ".*Assertion.*failed.*");
  s21::Graph graph_1(2);
  s21::Graph graph_2(10);
  EXPECT_EQ(graph_2(0, 0), 0);
  EXPECT_EQ(graph_2(9, 9), 0);
  ASSERT_DEATH(graph_2(10, 10), ".*Assertion.*failed.*");
}

TEST(graph, constructor_from_file) {
  s21::Graph graph(CMAKE_CURRENT_SOURCE_DIR"/graph_raw_file");
  double graph_raw[] = {0,   29,  20,  21,  16,  31,  100, 12,  4,   31,  18,
                    29,  0,   15,  29,  28,  40,  72,  21,  29,  41,  12,
                    20,  15,  0,   15,  14,  25,  81,  9,   23,  27,  13,
                    21,  29,  15,  0,   4,   12,  92,  12,  25,  13,  25,
                    16,  28,  14,  4,   0,   16,  94,  9,   20,  16,  22,
                    31,  40,  25,  12,  16,  0,   95,  24,  36,  3,   37,
                    100, 72,  81,  92,  94,  95,  0,   90,  101, 99,  84,
                    12,  21,  9,   12,  9,   24,  90,  0,   15,  25,  13,
                    4,   29,  23,  25,  20,  36,  101, 15,  0,   35,  18,
                    31,  41,  27,  13,  16,  3,   99,  25,  35,  0,   38,
                    18,  12,  13,  25,  22,  37,  84,  13,  18,  38,  0};
  size_t graph_size = graph.Size();
  EXPECT_EQ(graph_size, 11);
  for(size_t y = 0; y < graph_size; y++) {
    for(size_t x = 0; x < graph_size; x++) {
      EXPECT_EQ(graph(y, x), graph_raw[x + graph_size * y]);
    }
  }
}

TEST(graph, constructor_from_raw) {
  double graph_raw[] = {0,   29,  20,  21,  16,  31,  100, 12,  4,   31,  18,
                    29,  0,   15,  29,  28,  40,  72,  21,  29,  41,  12,
                    20,  15,  0,   15,  14,  25,  81,  9,   23,  27,  13,
                    21,  29,  15,  0,   4,   12,  92,  12,  25,  13,  25,
                    16,  28,  14,  4,   0,   16,  94,  9,   20,  16,  22,
                    31,  40,  25,  12,  16,  0,   95,  24,  36,  3,   37,
                    100, 72,  81,  92,  94,  95,  0,   90,  101, 99,  84,
                    12,  21,  9,   12,  9,   24,  90,  0,   15,  25,  13,
                    4,   29,  23,  25,  20,  36,  101, 15,  0,   35,  18,
                    31,  41,  27,  13,  16,  3,   99,  25,  35,  0,   38,
                    18,  12,  13,  25,  22,  37,  84,  13,  18,  38,  0};
  s21::Graph graph(graph_raw, 11);
  size_t graph_size = graph.Size();
  EXPECT_EQ(graph_size, 11);
  for(size_t y = 0; y < graph_size; y++) {
    for(size_t x = 0; x < graph_size; x++) {
      EXPECT_EQ(graph(y, x), graph_raw[x + graph_size * y]);
    }
  }
}

TEST(graph, constructor_from_file_fail_1) {
  EXPECT_ANY_THROW(s21::Graph graph(CMAKE_CURRENT_SOURCE_DIR"/graph_raw_file_broken1"));
}

TEST(graph, constructor_from_file_fail_2) {
  EXPECT_ANY_THROW(s21::Graph graph(CMAKE_CURRENT_SOURCE_DIR"/graph_raw_file_broken2"));
}

TEST(graph, constructor_from_file_fail_3) {
  EXPECT_ANY_THROW(s21::Graph graph(CMAKE_CURRENT_SOURCE_DIR"/graph_raw_file_broken3"));
}

TEST(graph, constructor_from_file_fail_4) {
  EXPECT_ANY_THROW(s21::Graph graph(CMAKE_CURRENT_SOURCE_DIR"/graph_raw_file_broken4"));
}

TEST(graph, constructor_from_file_fail_5) {
  EXPECT_ANY_THROW(s21::Graph graph(CMAKE_CURRENT_SOURCE_DIR"/graph_raw_file_broken5"));
}
