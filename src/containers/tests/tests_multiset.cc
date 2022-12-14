// Copyright <lwolmer> 2022
#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>

#include <iostream>
#include <set>
#include <stdexcept>
#include <utility>

#include "s21_containers.h"
#include "s21_containersplus.h"

template <class key>
void ASSERT_MULTISET(std::multiset<key> stl, s21::multiset<key> s21) {
  // Proper way, but cppcheck, sigh...
  // ASSERT_TRUE(stl.size() == s21.size() &&
  // std::equal(stl.begin(), s21.end(), s21.begin()))
  typename std::multiset<key>::iterator stl_it = stl.begin();
  typename s21::multiset<key>::iterator s21_it = s21.begin();
  ASSERT_EQ(stl.size(), s21.size());
  while (stl_it != stl.end() && s21_it != s21.end()) {
    ASSERT_EQ(*s21_it, *stl_it);
    ++stl_it;
    ++s21_it;
  }

  ASSERT_TRUE(stl_it == stl.end() && s21_it == s21.end());
}

TEST(multiset, init) {
  std::multiset<std::string> stl;
  s21::multiset<std::string> s21 = s21::multiset<std::string>();
  stl.insert("one");
  s21.insert("one");
  stl.insert("two");
  s21.insert("two");
  stl.insert("two");
  s21.insert("two");

  ASSERT_EQ(stl.size(), s21.size());
  ASSERT_NE(stl.find("one"), stl.end());
  ASSERT_TRUE(s21.contains("one"));
  ASSERT_NE(stl.find("two"), stl.end());
  ASSERT_TRUE(s21.contains("two"));

  s21::multiset<std::string> C3 = s21;
  s21::multiset<std::string> C4 = std::move(s21);
  ASSERT_EQ(stl.size(), C3.size());
  ASSERT_TRUE(C3.contains("one"));
  ASSERT_TRUE(C3.contains("two"));
  ASSERT_EQ(stl.size(), C4.size());
  ASSERT_TRUE(C4.contains("one"));
  ASSERT_TRUE(C4.contains("two"));
}

TEST(multiset, move) {
  std::multiset<int> stl = {1, 2, 3};
  s21::multiset<int> s21 = {1, 2, 3};
  s21::multiset<int> s21_moved;
  s21_moved = std::move(s21);

  ASSERT_MULTISET(stl, s21_moved);
}

TEST(multiset, insert_contains) {
  std::multiset<int> stl = {1, 2, 3};
  s21::multiset<int> s21 = {1, 2, 3};

  stl.insert(2);
  s21.insert(2);
  ASSERT_MULTISET(stl, s21);
}

TEST(multiset, find) {
  std::multiset<std::string> stl = {"one", "two", "two", "three"};
  s21::multiset<std::string> s21 = {"one", "two", "two", "three"};

  auto stl_it = stl.find("two");
  auto s21_it = s21.find("two");
  ASSERT_EQ(*stl_it, *s21_it);
}

TEST(multiset, find_not_exist) {
  std::multiset<std::string> stl = {"one", "two", "two", "three"};
  s21::multiset<std::string> s21 = {"one", "two", "two", "three"};

  auto stl_it = stl.find("seven");
  auto s21_it = s21.find("seven");
  ASSERT_EQ(stl_it, stl.end());
  ASSERT_EQ(s21_it, s21.end());
}

TEST(multiset, empty) {
  std::multiset<int> stl;
  s21::multiset<int> s21;

  ASSERT_TRUE(stl.empty() && s21.empty());
  ASSERT_TRUE(stl.begin() == stl.end() && s21.begin() == s21.end());
}

TEST(multiset, max_size) {
  std::multiset<int> stl;
  s21::multiset<int> s21;

  ASSERT_EQ(stl.max_size(), s21.max_size());
}

TEST(multiset, empty_not_empty) {
  std::multiset<std::string> stl = {"one", "two", "two", "three"};
  s21::multiset<std::string> s21 = {"one", "two", "two", "three"};

  ASSERT_TRUE(!stl.empty() && !s21.empty());
  ASSERT_TRUE(stl.begin() != stl.end() && s21.begin() != s21.end());
}

TEST(multiset, max_clear_eraze) {
  std::multiset<std::string> stl = {"one", "two", "two", "two", "three"};
  s21::multiset<std::string> s21 = {"one", "two", "two", "two", "three"};
  stl.erase(stl.find("two"));
  s21.erase(s21.find("two"));
  ASSERT_MULTISET(stl, s21);
  stl.erase("two");
  s21.erase("two");
  ASSERT_MULTISET(stl, s21);
  stl.insert("seven");
  s21.insert("seven");
  ASSERT_MULTISET(stl, s21);
  stl.clear();
  s21.clear();
  ASSERT_MULTISET(stl, s21);
}

TEST(multiset, swap) {
  std::multiset<std::string> stl_1 = {"one", "two", "three"};
  std::multiset<std::string> stl_2 = {"two"};

  s21::multiset<std::string> s21_1 = {"one", "two", "three"};
  s21::multiset<std::string> s21_2 = {"two"};

  stl_1.swap(stl_2);
  s21_1.swap(s21_2);

  ASSERT_MULTISET(stl_1, s21_1);
}

TEST(multiset, merge) {
  std::multiset<std::string> stl_1 = {"one", "two", "three"};
  std::multiset<std::string> stl_2 = {"two"};

  s21::multiset<std::string> s21_1 = {"one", "two", "three"};
  s21::multiset<std::string> s21_2 = {"two"};

  stl_1.merge(stl_2);
  s21_1.merge(s21_2);

  ASSERT_MULTISET(stl_1, s21_1);
}

TEST(multiset, emplace) {
  std::multiset<std::string> stl;
  s21::multiset<std::string> s21;

  stl.emplace("123");
  s21.emplace("123");
  ASSERT_MULTISET(stl, s21);
  stl.emplace("1");
  stl.emplace("2");
  stl.emplace("3");
  s21.emplace("1", "2", "3");
  ASSERT_MULTISET(stl, s21);
  stl.emplace("4");
  stl.emplace("5");
  stl.emplace("6");
  stl.emplace("7");
  stl.emplace("8");
  s21.emplace("4", "5", "6", "7", "8");
  ASSERT_MULTISET(stl, s21);
  stl.emplace();
  s21.emplace();
  ASSERT_MULTISET(stl, s21);
  std::string str = "str";
  stl.emplace("9");
  stl.emplace(str);
  stl.emplace("10");
  s21.emplace("9", str, "10");
  ASSERT_MULTISET(stl, s21);
}

TEST(multiset, lower_bound) {
  std::multiset<int> stl = {1, 2, 2, 3, 5};
  s21::multiset<int> s21 = {1, 2, 2, 3, 5};

  auto stl_it = stl.lower_bound(2);
  auto s21_it = s21.lower_bound(2);

  ASSERT_EQ(*stl_it, *s21_it);
}

TEST(multiset, lower_bound_no_key) {
  std::multiset<int> stl = {1, 2, 4, 5};
  s21::multiset<int> s21 = {1, 2, 4, 5};

  auto stl_it = stl.lower_bound(3);
  auto s21_it = s21.lower_bound(3);
  ASSERT_EQ(*stl_it, *s21_it);
}

TEST(multiset, lower_bound_no_key_out_of_bound) {
  std::multiset<int> stl = {1, 2, 4, 5};
  s21::multiset<int> s21 = {1, 2, 4, 5};

  auto stl_it = stl.lower_bound(6);
  auto s21_it = s21.lower_bound(6);

  ASSERT_EQ(stl_it, stl.end());
  ASSERT_EQ(s21_it, s21.end());
}

TEST(multiset, equal_range) {
  std::multiset<int> stl = {1, 2, 2, 3, 5};
  s21::multiset<int> s21 = {1, 2, 2, 3, 5};

  auto stl_pair = stl.equal_range(2);
  auto s21_pair = s21.equal_range(2);

  ASSERT_EQ(*stl_pair.first, *s21_pair.first);
  ASSERT_EQ(*stl_pair.second, *s21_pair.second);
}

TEST(multiset, equal_range_not_exist_between) {
  std::multiset<int> stl = {1, 2, 4, 5};
  s21::multiset<int> s21 = {1, 2, 4, 5};

  auto stl_pair = stl.equal_range(3);
  auto s21_pair = s21.equal_range(3);

  ASSERT_EQ(*stl_pair.first, *s21_pair.first);
  ASSERT_EQ(*stl_pair.second, *s21_pair.second);
}

TEST(multiset, equal_range_edge_1) {
  std::multiset<int> stl = {1, 2, 4, 5};
  s21::multiset<int> s21 = {1, 2, 4, 5};

  auto stl_pair = stl.equal_range(1);
  auto s21_pair = s21.equal_range(1);

  ASSERT_EQ(*stl_pair.first, *s21_pair.first);
  ASSERT_EQ(*stl_pair.second, *s21_pair.second);
}

TEST(multiset, equal_range_edge_2) {
  std::multiset<int> stl = {1, 2, 4, 5};
  s21::multiset<int> s21 = {1, 2, 4, 5};

  auto stl_pair = stl.equal_range(5);
  auto s21_pair = s21.equal_range(5);

  ASSERT_EQ(*stl_pair.first, *s21_pair.first);
  ASSERT_EQ(stl_pair.second, stl.end());
  ASSERT_EQ(s21_pair.second, s21.end());
}

TEST(multiset, equal_range_not_exist_out_of_bounds) {
  std::multiset<int> stl = {1, 2, 4, 5};
  s21::multiset<int> s21 = {1, 2, 4, 5};

  auto stl_pair = stl.equal_range(6);
  auto s21_pair = s21.equal_range(6);

  ASSERT_EQ(stl_pair.first, stl.end());
  ASSERT_EQ(s21_pair.first, s21.end());
  ASSERT_EQ(stl_pair.second, stl.end());
  ASSERT_EQ(s21_pair.second, s21.end());
}

TEST(multiset, upper_bound) {
  std::multiset<int> stl = {1, 2, 2, 3, 5};
  s21::multiset<int> s21 = {1, 2, 2, 3, 5};

  auto stl_it = stl.upper_bound(2);
  auto s21_it = s21.upper_bound(2);
  ASSERT_EQ(*stl_it, *s21_it);
}

TEST(multiset, upper_bound_no_key) {
  std::multiset<int> stl = {1, 2, 4, 5};
  s21::multiset<int> s21 = {1, 2, 4, 5};

  auto stl_it = stl.upper_bound(3);
  auto s21_it = s21.upper_bound(3);

  ASSERT_EQ(*stl_it, *s21_it);
}

TEST(multiset, upper_bound_no_key_out_of_bound) {
  std::multiset<int> stl = {1, 2, 4, 5};
  s21::multiset<int> s21 = {1, 2, 4, 5};

  auto stl_it = stl.upper_bound(6);
  auto s21_it = s21.upper_bound(6);

  ASSERT_EQ(stl_it, stl.end());
  ASSERT_EQ(s21_it, s21.end());
}

TEST(multiset, count) {
  std::multiset<int> stl = {1, 2, 2, 3, 5};
  s21::multiset<int> s21 = {1, 2, 2, 3, 5};

  size_t stl_count = stl.count(2);
  size_t s21_count = s21.count(2);

  ASSERT_EQ(stl_count, s21_count);
}

TEST(multiset, count_zero) {
  std::multiset<int> stl = {1, 2, 2, 3, 5};
  s21::multiset<int> s21 = {1, 2, 2, 3, 5};

  size_t stl_count = stl.count(4);
  size_t s21_count = s21.count(4);

  ASSERT_EQ(stl_count, s21_count);
}

TEST(multiset, const_iterator) {
  s21::multiset<int> s21 = {1, 1, 2, 3};

  s21::multiset<int>::const_iterator it =
      s21::multiset<int>::const_iterator(s21.begin());
  ++it;
  ASSERT_EQ(*it, 1);
}
