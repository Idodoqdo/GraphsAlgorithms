// Copyright <lwolmer, lshiela, jgerrick> 2022
#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
