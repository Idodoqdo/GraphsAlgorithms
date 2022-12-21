// Copyright <lwolmer, lshiela, jgerrick> 2022
#include <gtest/gtest.h>
#include <rand_generator.h>

TEST(rand_gen, int_test_1) {
  s21::RandomNumberGenerator rng = s21::RandomNumberGenerator();
  int lower_bound = -10, upper_bound = 10;
  int val = rng.GenerateRandomInt(lower_bound, upper_bound);
  EXPECT_LE(val, upper_bound);
  EXPECT_GE(val, lower_bound);
}

TEST(rand_gen, int_test_2) {
  s21::RandomNumberGenerator rng = s21::RandomNumberGenerator();
  int lower_bound = -999, upper_bound = 0;
  int val = rng.GenerateRandomInt(lower_bound, upper_bound);
  EXPECT_LE(val, upper_bound);
  EXPECT_GE(val, lower_bound);
}

TEST(rand_gen, int_test_3) {
  s21::RandomNumberGenerator rng = s21::RandomNumberGenerator();
  int lower_bound = -999, upper_bound = 0;
  rng.SetSeed(24);
  int val1 = rng.GenerateRandomInt(lower_bound, upper_bound);
  rng.SetSeed(24);
  int val2 = rng.GenerateRandomInt(lower_bound, upper_bound);

  EXPECT_EQ(val1, val2);
}

TEST(rand_gen, double_test_1) {
  s21::RandomNumberGenerator rng = s21::RandomNumberGenerator();
  int lower_bound = -10, upper_bound = 10;
  double val = rng.GenerateRandomDouble(lower_bound, upper_bound);
  EXPECT_LE(val, upper_bound);
  EXPECT_GE(val, lower_bound);
}

TEST(rand_gen, double_test_2) {
  s21::RandomNumberGenerator rng = s21::RandomNumberGenerator();
  int lower_bound = -999, upper_bound = 0;
  double val = rng.GenerateRandomDouble(lower_bound, upper_bound);
  EXPECT_LE(val, upper_bound);
  EXPECT_GE(val, lower_bound);
}

TEST(rand_gen, double_test_3) {
  s21::RandomNumberGenerator rng = s21::RandomNumberGenerator();
  int lower_bound = 0, upper_bound = 1;
  rng.SetSeed(24);
  double val1 = rng.GenerateRandomDouble(lower_bound, upper_bound);
  rng.SetSeed(24);
  double val2 = rng.GenerateRandomDouble(lower_bound, upper_bound);
  EXPECT_EQ(val1, val2);
}