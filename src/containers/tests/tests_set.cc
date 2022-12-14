// Copyright <lwolmer> 2022
#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>

#include <iostream>
#include <set>
#include <stdexcept>
#include <utility>

#include "s21_containers.h"

template <class key>
void ASSERT_SET(std::set<key> stl, s21::set<key> s21) {
  // Proper way, but cppcheck, sigh...
  // ASSERT_TRUE(stl.size() == s21.size() &&
  // std::equal(stl.begin(), s21.end(), s21.begin()))
  typename std::set<key>::iterator stl_it = stl.begin();
  typename s21::set<key>::iterator s21_it = s21.begin();
  ASSERT_EQ(stl.size(), s21.size());
  while (stl_it != stl.end() && s21_it != s21.end()) {
    ASSERT_EQ(*s21_it, *stl_it);
    ++stl_it;
    ++s21_it;
  }

  ASSERT_TRUE(stl_it == stl.end() && s21_it == s21.end());
}

TEST(set, init) {
  std::set<std::string> stl;
  s21::set<std::string> s21 = s21::set<std::string>();
  stl.insert("one");
  s21.insert("one");
  stl.insert("two");
  s21.insert("two");

  ASSERT_EQ(stl.size(), s21.size());
  ASSERT_NE(stl.find("one"), stl.end());
  ASSERT_TRUE(s21.contains("one"));
  ASSERT_NE(stl.find("two"), stl.end());
  ASSERT_TRUE(s21.contains("two"));

  s21::set<std::string> C3 = s21;
  s21::set<std::string> C4 = std::move(s21);
  ASSERT_EQ(stl.size(), C3.size());
  ASSERT_TRUE(C3.contains("one"));
  ASSERT_TRUE(C3.contains("two"));
  ASSERT_EQ(stl.size(), C4.size());
  ASSERT_TRUE(C4.contains("one"));
  ASSERT_TRUE(C4.contains("two"));
}

TEST(set, move) {
  std::set<int> stl = {1, 2, 3};
  s21::set<int> s21 = {1, 2, 3};
  s21::set<int> s21_moved;
  s21_moved = std::move(s21);

  ASSERT_SET(stl, s21_moved);
}

TEST(set, insert_contains) {
  std::set<int> stl = {1, 2, 3};
  s21::set<int> s21 = {1, 2, 3};

  stl.insert(2);
  s21.insert(2);
  ASSERT_SET(stl, s21);
}

TEST(set, find) {
  std::set<std::string> stl = {"one", "two", "three"};
  s21::set<std::string> s21 = {"one", "two", "three"};

  auto stl_it = stl.find("two");
  auto s21_it = s21.find("two");
  ASSERT_EQ(*stl_it, *s21_it);
}

TEST(set, empty) {
  std::set<int> stl;
  s21::set<int> s21;

  ASSERT_TRUE(stl.empty() && s21.empty());
  ASSERT_TRUE(stl.begin() == stl.end() && s21.begin() == s21.end());
}

TEST(set, max_size) {
  std::set<int> stl;
  s21::set<int> s21;

  ASSERT_EQ(stl.max_size(), s21.max_size());
}

TEST(set, empty_not_empty) {
  std::set<std::string> stl = {"one", "two", "three"};
  s21::set<std::string> s21 = {"one", "two", "three"};

  ASSERT_TRUE(!stl.empty() && !s21.empty());
}

TEST(set, max_clear_eraze) {
  std::set<std::string> stl = {"one", "two", "three"};
  s21::set<std::string> s21 = {"one", "two", "three"};

  stl.erase("two");
  s21.erase("two");
  ASSERT_SET(stl, s21);
  stl.insert("seven");
  s21.insert("seven");
  ASSERT_SET(stl, s21);
  stl.clear();
  s21.clear();
  ASSERT_SET(stl, s21);
}

TEST(set, swap) {
  std::set<std::string> stl_1 = {"one", "three"};
  std::set<std::string> stl_2 = {"two"};

  s21::set<std::string> s21_1 = {"one", "three"};
  s21::set<std::string> s21_2 = {"two"};

  stl_1.swap(stl_2);
  s21_1.swap(s21_2);

  ASSERT_SET(stl_1, s21_1);
}

TEST(set, merge) {
  std::set<std::string> stl_1 = {"one", "three"};
  std::set<std::string> stl_2 = {"two"};

  s21::set<std::string> s21_1 = {"one", "three"};
  s21::set<std::string> s21_2 = {"two"};

  stl_1.merge(stl_2);
  s21_1.merge(s21_2);

  ASSERT_SET(stl_1, s21_1);
}

TEST(set, emplace) {
  std::set<std::string> stl;
  s21::set<std::string> s21;

  stl.emplace("123");
  s21.emplace("123");
  ASSERT_SET(stl, s21);
  stl.emplace("1");
  stl.emplace("2");
  stl.emplace("3");
  s21.emplace("1", "2", "3");
  ASSERT_SET(stl, s21);
  stl.emplace("4");
  stl.emplace("5");
  stl.emplace("6");
  stl.emplace("7");
  stl.emplace("8");
  s21.emplace("4", "5", "6", "7", "8");
  ASSERT_SET(stl, s21);
  stl.emplace();
  s21.emplace();
  ASSERT_SET(stl, s21);
  std::string str = "str";
  stl.emplace("9");
  stl.emplace(str);
  stl.emplace("10");
  s21.emplace("9", str, "10");
  ASSERT_SET(stl, s21);
}

TEST(set, const_iterator) {
  s21::set<int> s21 = {1, 2, 3};

  s21::set<int>::const_iterator it = s21::set<int>::const_iterator(s21.begin());
  ++it;
  ASSERT_EQ(*it, 2);
}
