#include <gtest/gtest.h>

#include <array>

#include "s21_array.h"

template <typename T, size_t N>
bool comparison(std::array<T, N> a, s21::array<T, N> b) {
  bool result = true;
  if (a.size() != b.size()) {
    result = false;
  } else if (a.size() > 0) {
    auto iterator_a = a.begin();
    auto iterator_b = b.begin();
    while (iterator_a != a.end() && iterator_b != b.end() && result) {
      if (*iterator_a != *iterator_b) {
        result = false;
      }
      ++iterator_a;
      ++iterator_b;
    }
  }
  return result;
}

TEST(ArrayTest, constructor_0) {
  std::array<int, 0> lib;
  s21::array<int, 0> my;
  ASSERT_EQ(lib.size(), my.size());
}

TEST(ArrayTest, constructor_1) {
  std::array<int, 4> lib;
  s21::array<int, 4> my;
  ASSERT_EQ(lib.size(), my.size());
}

TEST(ArrayTest, constructor_2) {
  std::array<int, 4> lib{4, 7, 3, 5};
  s21::array<int, 4> my{4, 7, 3, 5};
  ASSERT_TRUE(comparison(lib, my));
}

TEST(ArrayTest, constructor_3) {
  std::array<int, 4> lib{4, 7, 9, 5};
  s21::array<int, 4> my{4, 7, 3, 5};
  ASSERT_FALSE(comparison(lib, my));
}

TEST(ArrayTest, constructor_4) {
  std::array<int, 4> lib{4, 7, 5};
  s21::array<int, 4> my{4, 7, 3, 5};
  ASSERT_FALSE(comparison(lib, my));
}

TEST(ArrayTest, constructor_8) {
  std::array<int, 4> lib{4, 7, 3, 5};
  std::array<int, 4> lib2 = std::move(lib);
  s21::array<int, 4> my{4, 7, 3, 5};
  s21::array<int, 4> my2 = std::move(my);
  ASSERT_TRUE(comparison(lib2, my2));
}

TEST(ArrayTest, operator_overload_1) {
  std::array<int, 4> lib;
  lib = {4, 7, 3, 5};
  s21::array<int, 4> my;
  my = {4, 7, 3, 5};
  ASSERT_TRUE(comparison(lib, my));
}

TEST(ArrayTest, constructor_2_0) {
  std::array<int, 0> lib{};
  s21::array<int, 0> my{};
  ASSERT_TRUE(comparison(lib, my));
}

TEST(ArrayTest, constructor_8_0) {
  std::array<int, 0> lib{};
  std::array<int, 0> lib2 = std::move(lib);
  s21::array<int, 0> my{};
  s21::array<int, 0> my2 = std::move(my);
  ASSERT_TRUE(comparison(lib2, my2));
}

TEST(ArrayTest, operator_overload_1_0) {
  std::array<int, 0> lib;
  lib = {};
  s21::array<int, 0> my;
  my = {};
  ASSERT_TRUE(comparison(lib, my));
}

TEST(ArrayTest, function_at) {
  std::array<int, 4> lib = {10, 15, 30};
  s21::array<int, 4> my = {10, 20, 30};
  ASSERT_EQ(lib.at(2), my.at(2));
}

TEST(ArrayTest, function_at_ex) {
  s21::array<int, 4> my = {10, 20, 30};
  ASSERT_ANY_THROW(my.at(5));
}

TEST(ArrayTest, function_operator_1) {
  std::array<int, 3> lib = {10, 20, 30};
  lib[1] = 4;
  s21::array<int, 3> my = {10, 20, 30};
  my[1] = 4;
  ASSERT_TRUE(comparison(lib, my));
  ASSERT_EQ(lib[2], my[2]);
}

TEST(ArrayTest, function_front) {
  std::array<int, 4> lib = {10, 15, 30};
  s21::array<int, 4> my = {10, 20, 30};
  ASSERT_EQ(lib.front(), my.front());
}

TEST(ArrayTest, function_back) {
  std::array<int, 3> lib = {10, 15, 30};
  s21::array<int, 3> my = {10, 20, 30};
  ASSERT_EQ(lib.back(), my.back());
}

TEST(ArrayTest, function_begin) {
  std::array<int, 3> lib = {10, 20, 30};
  s21::array<int, 3> my = {10, 20, 30};
  ASSERT_EQ(*(lib.begin()), *(my.begin()));
  ASSERT_TRUE(comparison(lib, my));
}

TEST(ArrayTest, function_begin_end) {
  std::array<int, 0> lib;
  s21::array<int, 0> my;
  ASSERT_TRUE(lib.begin() == lib.end());
  ASSERT_TRUE(my.begin() == my.end());
}

TEST(ArrayTest, function_begin_plus) {
  std::array<int, 3> lib = {10, 20, 30};
  std::array<int, 3>::iterator lib_iter = lib.begin();
  ++lib_iter;
  s21::array<int, 3> my = {10, 20, 30};
  s21::array<int, 3>::iterator my_iter = my.begin();
  ++my_iter;
  ASSERT_EQ(*lib_iter, *my_iter);
  ASSERT_TRUE(comparison(lib, my));
}

TEST(ArrayTest, function_end_minus) {
  std::array<int, 3> lib = {10, 20, 30};
  std::array<int, 3>::iterator lib_iter = lib.end();
  --lib_iter;
  s21::array<int, 3> my = {10, 20, 30};
  s21::array<int, 3>::iterator my_iter = my.end();
  --my_iter;
  ASSERT_EQ(*lib_iter, *my_iter);
  ASSERT_TRUE(comparison(lib, my));
}

TEST(ArrayTest, function_cbegin_plus) {
  std::array<int, 3> lib = {10, 20, 30};
  std::array<int, 3>::const_iterator lib_iter = lib.cbegin();
  ++lib_iter;
  s21::array<int, 3> my = {10, 20, 30};
  s21::array<int, 3>::const_iterator my_iter = my.cbegin();
  ++my_iter;
  ASSERT_EQ(*lib_iter, *my_iter);
  ASSERT_TRUE(comparison(lib, my));
}

TEST(ArrayTest, function_cend_minus) {
  std::array<int, 3> lib = {10, 20, 30};
  std::array<int, 3>::const_iterator lib_iter = lib.cend();
  --lib_iter;
  s21::array<int, 3> my = {10, 20, 30};
  s21::array<int, 3>::const_iterator my_iter = my.cend();
  --my_iter;
  ASSERT_EQ(*lib_iter, *my_iter);
  ASSERT_TRUE(comparison(lib, my));
}

TEST(ArrayTest, function_iter_eq) {
  s21::array<int, 3> my = {10, 20, 30};
  s21::array<int, 3>::iterator iter1 = my.begin();
  s21::array<int, 3>::iterator iter2 = my.begin();
  ASSERT_TRUE(iter1 == iter2);
}

TEST(ArrayTest, function_iter_uneq) {
  s21::array<int, 3> my = {10, 20, 30};
  s21::array<int, 3>::iterator iter1 = my.begin();
  s21::array<int, 3>::iterator iter2 = my.begin();
  ++iter2;
  ASSERT_TRUE(iter1 != iter2);
}

TEST(ArrayTest, function_empty_1) {
  s21::array<int, 3> my{10, 20, 30};
  ASSERT_FALSE(my.empty());
}

TEST(ArrayTest, function_empty_2) {
  s21::array<int, 0> my;
  ASSERT_TRUE(my.empty());
}

TEST(ArrayTest, function_max_size) {
  std::array<int, 3> lib;
  s21::array<int, 3> my;
  ASSERT_EQ(lib.max_size(), my.max_size());
}

TEST(ArrayTest, function_swap) {
  std::array<int, 4> lib1{10, 20, 30, 40};
  std::array<int, 4> lib2{1, 7, 9, 11};
  s21::array<int, 4> my1{10, 20, 30, 40};
  s21::array<int, 4> my2{1, 7, 9, 11};
  lib1.swap(lib2);
  my1.swap(my2);
  ASSERT_TRUE(comparison(lib1, my1));
  ASSERT_TRUE(comparison(lib2, my2));
}

TEST(ArrayTest, function_fill) {
  std::array<int, 20> lib;
  s21::array<int, 20> my;
  lib.fill(14);
  my.fill(14);
  ASSERT_TRUE(comparison(lib, my));
}
