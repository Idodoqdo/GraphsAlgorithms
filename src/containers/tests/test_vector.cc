#include <gtest/gtest.h>

#include <vector>

#include "s21_vector.h"

template <typename T>
bool comparison(std::vector<T> a, s21::vector<T> b) {
  bool result = true;
  if (a.size() != b.size() || a.capacity() != b.capacity()) {
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

TEST(VectorTest, constructor_1) {
  std::vector<int> lib;
  s21::vector<int> my;
  ASSERT_TRUE(comparison(lib, my));
}

TEST(VectorTest, constructor_2) {
  std::vector<int> lib(4);
  s21::vector<int> my(4);
  ASSERT_TRUE(comparison(lib, my));
}

TEST(VectorTest, constructor_3) {
  std::vector<int> lib(3);
  s21::vector<int> my(4);
  ASSERT_FALSE(comparison(lib, my));
}

TEST(VectorTest, constructor_4) {
  std::vector<int> lib{10, 20, 30};
  s21::vector<int> my{10, 20, 30};
  ASSERT_TRUE(comparison(lib, my));
}

TEST(VectorTest, constructor_5) {
  std::vector<int> lib = {10, 20, 30};
  s21::vector<int> my = {10, 20, 30};
  ASSERT_TRUE(comparison(lib, my));
}

TEST(VectorTest, constructor_6) {
  std::vector<int> lib = {10, 15, 30};
  s21::vector<int> my = {10, 20, 30};
  ASSERT_FALSE(comparison(lib, my));
}

TEST(VectorTest, constructor_7) {
  std::vector<int> lib = {10, 20, 30};
  s21::vector<int> my = {10, 20, 30, 40};
  ASSERT_FALSE(comparison(lib, my));
}

TEST(VectorTest, constructor_8) {
  std::vector<int> lib = {10, 20, 30};
  std::vector<int> lib2 = std::move(lib);
  s21::vector<int> my = {10, 20, 30};
  s21::vector<int> my2 = std::move(my);
  ASSERT_TRUE(comparison(lib2, my2));
}

TEST(VectorTest, constructor_9) {
  std::vector<int> lib = {10, 20, 30};
  std::vector<int> lib2 = std::move(lib);
  s21::vector<int> my = {10, 20, 30, 40};
  s21::vector<int> my2 = std::move(my);
  ASSERT_FALSE(comparison(lib2, my2));
}

TEST(VectorTest, operator_overload_1) {
  std::vector<int> lib;
  lib = {10, 20, 30};
  s21::vector<int> my;
  my = {10, 20, 30};
  ASSERT_TRUE(comparison(lib, my));
}

TEST(VectorTest, operator_overload_2) {
  std::vector<int> lib;
  lib = {10, 20, 30, 40};
  s21::vector<int> my;
  my = {10, 20, 30};
  ASSERT_FALSE(comparison(lib, my));
}

TEST(VectorTest, function_at) {
  std::vector<int> lib = {10, 15, 30};
  s21::vector<int> my = {10, 20, 30};
  ASSERT_EQ(lib.at(2), my.at(2));
}

TEST(VectorTest, function_at_ex) {
  s21::vector<int> my = {10, 20, 30};
  ASSERT_ANY_THROW(my.at(5));
}

TEST(VectorTest, function_operator_1) {
  std::vector<int> lib = {10, 20, 30};
  lib[1] = 4;
  s21::vector<int> my = {10, 20, 30};
  my[1] = 4;
  ASSERT_TRUE(comparison(lib, my));
  ASSERT_EQ(lib[2], my[2]);
}

TEST(VectorTest, function_front) {
  std::vector<int> lib = {10, 20, 30};
  s21::vector<int> my = {10, 20, 30};
  ASSERT_EQ(lib.front(), my.front());
  ASSERT_TRUE(comparison(lib, my));
}

TEST(VectorTest, function_back) {
  std::vector<int> lib = {10, 20, 30};
  s21::vector<int> my = {10, 20, 30};
  ASSERT_EQ(lib.back(), my.back());
  ASSERT_TRUE(comparison(lib, my));
}

TEST(VectorTest, function_data) {
  std::vector<int> lib = {10, 20, 30};
  s21::vector<int> my = {10, 20, 30};
  ASSERT_EQ(lib.data()[0], my.data()[0]);
  ASSERT_EQ(lib.data()[1], my.data()[1]);
  ASSERT_EQ(lib.data()[2], my.data()[2]);
}

TEST(VectorTest, function_begin) {
  std::vector<int> lib = {10, 20, 30};
  s21::vector<int> my = {10, 20, 30};
  ASSERT_EQ(*(lib.begin()), *(my.begin()));
  ASSERT_TRUE(comparison(lib, my));
}

TEST(VectorTest, function_begin_end) {
  std::vector<int> lib;
  s21::vector<int> my;
  ASSERT_TRUE(lib.begin() == lib.end());
  ASSERT_TRUE(my.begin() == my.end());
}

TEST(VectorTest, function_begin_plus) {
  std::vector<int> lib = {10, 20, 30};
  std::vector<int>::iterator lib_iter = lib.begin();
  ++lib_iter;
  s21::vector<int> my = {10, 20, 30};
  s21::vector<int>::iterator my_iter = my.begin();
  ++my_iter;
  ASSERT_EQ(*lib_iter, *my_iter);
  ASSERT_TRUE(comparison(lib, my));
}

TEST(VectorTest, function_end_minus) {
  std::vector<int> lib = {10, 20, 30};
  std::vector<int>::iterator lib_iter = lib.end();
  --lib_iter;
  s21::vector<int> my = {10, 20, 30};
  s21::vector<int>::iterator my_iter = my.end();
  --my_iter;
  ASSERT_EQ(*lib_iter, *my_iter);
  ASSERT_TRUE(comparison(lib, my));
}

TEST(VectorTest, function_cbegin_plus) {
  std::vector<int> lib{10, 20, 30};
  std::vector<int>::const_iterator lib_iter = lib.cbegin();
  ++lib_iter;
  s21::vector<int> my{10, 20, 30};
  s21::vector<int>::const_iterator my_iter = my.cbegin();
  ++my_iter;
  ASSERT_EQ(*lib_iter, *my_iter);
  ASSERT_TRUE(comparison(lib, my));
}

TEST(VectorTest, function_cend_minus) {
  std::vector<int> lib{10, 20, 30};
  std::vector<int>::const_iterator lib_iter = lib.cend();
  --lib_iter;
  s21::vector<int> my{10, 20, 30};
  s21::vector<int>::const_iterator my_iter = my.cend();
  --my_iter;
  ASSERT_EQ(*lib_iter, *my_iter);
  ASSERT_TRUE(comparison(lib, my));
}

TEST(VectorTest, function_iter_eq) {
  s21::vector<int> my{10, 20, 30};
  s21::vector<int>::iterator iter1 = my.begin();
  s21::vector<int>::iterator iter2 = my.begin();
  ASSERT_TRUE(iter1 == iter2);
}

TEST(VectorTest, function_iter_uneq) {
  s21::vector<int> my{10, 20, 30};
  s21::vector<int>::iterator iter1 = my.begin();
  s21::vector<int>::iterator iter2 = my.begin();
  ++iter2;
  ASSERT_TRUE(iter1 != iter2);
}

TEST(VectorTest, function_empty_1) {
  s21::vector<int> my{10, 20, 30};
  ASSERT_FALSE(my.empty());
}

TEST(VectorTest, function_empty_2) {
  s21::vector<int> my;
  ASSERT_TRUE(my.empty());
}

TEST(VectorTest, function_max_size) {
  std::vector<int> lib;
  s21::vector<int> my;
  ASSERT_EQ(lib.max_size(), my.max_size());
}

TEST(VectorTest, function_reserve) {
  std::vector<int> lib{10, 20, 30};
  lib.reserve(10);
  s21::vector<int> my{10, 20, 30};
  my.reserve(10);
  ASSERT_EQ(lib.capacity(), my.capacity());
}

TEST(VectorTest, function_shrink_to_fit) {
  std::vector<int> lib{10, 20, 30};
  lib.reserve(10);
  lib.shrink_to_fit();
  s21::vector<int> my{10, 20, 30};
  my.reserve(10);
  my.shrink_to_fit();
  ASSERT_EQ(lib.capacity(), my.capacity());
}

TEST(VectorTest, function_clear) {
  std::vector<int> lib{10, 20, 30};
  lib.clear();
  s21::vector<int> my{10, 20, 30};
  my.clear();
  ASSERT_EQ(lib.size(), my.size());
}

TEST(VectorTest, function_insert) {
  std::vector<int> lib{10, 20, 30};
  std::vector<int>::iterator lib_iter = lib.begin();
  ++lib_iter;
  lib.insert(lib_iter, 5);
  s21::vector<int> my{10, 20, 30};
  s21::vector<int>::iterator my_iter = my.begin();
  ++my_iter;
  my.insert(my_iter, 5);
  ASSERT_EQ(lib[1], my[1]);
  ASSERT_EQ(lib.size(), my.size());
}

TEST(VectorTest, function_erase) {
  std::vector<int> lib{10, 20, 30, 40};
  std::vector<int>::iterator lib_iter = lib.begin();
  ++lib_iter;
  lib.erase(lib_iter);
  s21::vector<int> my{10, 20, 30, 40};
  s21::vector<int>::iterator my_iter = my.begin();
  ++my_iter;
  my.erase(my_iter);
  ASSERT_EQ(lib[1], my[1]);
  ASSERT_EQ(lib.size(), my.size());
}

TEST(VectorTest, function_push_back) {
  std::vector<int> lib{10, 20, 30, 40};
  lib.push_back(5);
  s21::vector<int> my{10, 20, 30, 40};
  my.push_back(5);
  ASSERT_EQ(lib[4], my[4]);
  ASSERT_EQ(lib.size(), my.size());
}

TEST(VectorTest, function_pop_back) {
  std::vector<int> lib{10, 20, 30, 40};
  lib.pop_back();
  s21::vector<int> my{10, 20, 30, 40};
  my.pop_back();
  ASSERT_EQ(lib[2], my[2]);
  ASSERT_EQ(lib.size(), my.size());
}

TEST(VectorTest, function_swap) {
  std::vector<int> lib1{10, 20, 30, 40};
  std::vector<int> lib2{1, 7, 9, 11};
  s21::vector<int> my1{10, 20, 30, 40};
  s21::vector<int> my2{2, 4, 6};
  ASSERT_FALSE(comparison(lib2, my2));
  lib1.swap(lib2);
  my1.swap(my2);
  ASSERT_TRUE(comparison(lib2, my2));
}

TEST(VectorTest, function_emplace_0) {
  s21::vector<int> my{10, 20, 30, 40};
  s21::vector<int>::const_iterator my_iter = my.cbegin();
  ++my_iter;
  my.emplace(my_iter);
  std::vector<int> test{10, 20, 30, 40};
  ASSERT_TRUE(comparison(test, my));
}

TEST(VectorTest, function_emplace_1) {
  s21::vector<int> my{10, 20, 30, 40};
  s21::vector<int>::const_iterator my_iter = my.cbegin();
  ++my_iter;
  my.emplace(my_iter, 3);
  std::vector<int> test{10, 3, 20, 30, 40};
  ASSERT_TRUE(comparison(test, my));
}

TEST(VectorTest, function_emplace_3) {
  s21::vector<int> my{10, 20, 30, 40};
  s21::vector<int>::const_iterator my_iter = my.cbegin();
  ++my_iter;
  my.emplace(my_iter, 3, 7, 9);
  std::vector<int> test{10, 3, 7, 9, 20, 30, 40};
  ASSERT_TRUE(comparison(test, my));
}

TEST(VectorTest, function_emplace_5) {
  s21::vector<int> my{10, 20, 30, 40};
  s21::vector<int>::const_iterator my_iter = my.cbegin();
  ++my_iter;
  my.emplace(my_iter, 3, 7, 9, 4, 17);
  std::vector<int> test{10, 3, 7, 9, 4, 17, 20, 30, 40};
  ASSERT_TRUE(comparison(test, my));
}

TEST(VectorTest, function_emplace_back_0) {
  s21::vector<int> my{10, 20, 30, 40};
  my.emplace_back();
  std::vector<int> test{10, 20, 30, 40};
  ASSERT_TRUE(comparison(test, my));
}

TEST(VectorTest, function_emplace_back_1) {
  s21::vector<int> my{10, 20, 30, 40};
  my.emplace_back(3);
  std::vector<int> test{10, 20, 30, 40, 3};
  ASSERT_TRUE(comparison(test, my));
}

TEST(VectorTest, function_emplace_back_3) {
  s21::vector<int> my{10, 20, 30, 40};
  my.emplace_back(3, 7, 9);
  std::vector<int> test{10, 20, 30, 40, 3, 7, 9};
  ASSERT_TRUE(comparison(test, my));
}

TEST(VectorTest, function_emplace_back_5) {
  s21::vector<int> my{10, 20, 30, 40};
  my.emplace_back(3, 7, 9, 4, 17);
  std::vector<int> test{10, 20, 30, 40, 3, 7, 9, 4, 17};
  ASSERT_TRUE(comparison(test, my));
}
