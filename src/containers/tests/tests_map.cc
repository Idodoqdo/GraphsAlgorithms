// Copyright <lwolmer> 2022
#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>

#include <map>
#include <stdexcept>
#include <utility>

#include "s21_containers.h"

template <class key, class type>
void ASSERT_MAP(std::map<key, type> stl, s21::map<key, type> s21) {
  // Proper way, but cppcheck, sigh...
  // ASSERT_TRUE(stl.size() == s21.size() &&
  // std::equal(stl.begin(), s21.end(), s21.begin()))
  typename std::map<key, type>::iterator stl_it = stl.begin();
  typename s21::map<key, type>::iterator s21_it = s21.begin();
  ASSERT_EQ(stl.size(), s21.size());
  while (stl_it != stl.end() && s21_it != s21.end()) {
    ASSERT_EQ((*s21_it).first, stl_it->first);
    ASSERT_EQ((*s21_it).second, stl_it->second);
    ++stl_it;
    ++s21_it;
  }

  ASSERT_TRUE(stl_it == stl.end() && s21_it == s21.end());
}

TEST(map, init) {
  std::map<std::string, int> C1;
  s21::map<std::string, int> C2 = s21::map<std::string, int>();
  C1.insert(std::pair<std::string, int>("one", 1));
  C2.insert(std::pair<std::string, int>("one", 1));
  C1.insert(std::pair<std::string, int>("three", 3));
  C2.insert(std::pair<std::string, int>("three", 3));
  C1["five"] = 5;
  C2["five"] = 5;

  ASSERT_EQ(C1.size(), C2.size());
  ASSERT_EQ(C1["one"], C2["one"]);
  ASSERT_EQ(C1.at("three"), C2.at("three"));
  ASSERT_EQ(C1["five"], C2["five"]);

  EXPECT_THROW({ C2.at("seven"); }, std::out_of_range);

  s21::map<std::string, int> C3 = C2;
  s21::map<std::string, int> C4 = std::move(C2);
  ASSERT_EQ(C1.size(), C3.size());
  ASSERT_EQ(C1["one"], C3["one"]);
  ASSERT_EQ(C1["five"], C3["five"]);
  ASSERT_EQ(C1.size(), C4.size());
  ASSERT_EQ(C1["one"], C4["one"]);
  ASSERT_EQ(C1["five"], C4["five"]);
}

TEST(map, init_list) {
  std::map<std::string, int> stl = {{"one", 1}, {"two", 2}, {"three", 3}};
  s21::map<std::string, int> s21 = {{"one", 1}, {"two", 2}, {"three", 3}};

  ASSERT_MAP(stl, s21);
}

TEST(map, insert_contains) {
  std::map<std::string, int> stl = {{"one", 1}, {"two", 2}, {"three", 3}};
  s21::map<std::string, int> s21 = {{"one", 1}, {"two", 2}, {"three", 3}};

  stl.insert(std::pair<std::string, int>("two", 22));
  s21.insert(std::pair<std::string, int>("two", 22));
  ASSERT_MAP(stl, s21);
}

TEST(map, move) {
  std::map<std::string, int> stl = {{"one", 1}, {"two", 2}, {"three", 3}};
  s21::map<std::string, int> s21 = {{"one", 1}, {"two", 2}, {"three", 3}};
  s21::map<std::string, int> s21_moved;
  s21_moved = std::move(s21);

  ASSERT_MAP(stl, s21_moved);
}

TEST(map, destructor_for_coverage) {
  s21::map<std::string, int> *s21_1 = new s21::map<std::string, int>();
  delete s21_1;
}

TEST(map, empty) {
  std::map<std::string, int> stl = std::map<std::string, int>();
  s21::map<std::string, int> s21 = s21::map<std::string, int>();

  ASSERT_TRUE(stl.empty() && s21.empty());
  ASSERT_TRUE(stl.begin() == stl.end() && s21.begin() == s21.end());
}

TEST(map, empty_not_empty) {
  std::map<std::string, int> stl = {{"one", 1}, {"two", 2}, {"three", 3}};
  s21::map<std::string, int> s21 = {{"one", 1}, {"two", 2}, {"three", 3}};

  ASSERT_TRUE(!stl.empty() && !s21.empty());
  ASSERT_TRUE(stl.begin() != stl.end() && s21.begin() != s21.end());
}

TEST(map, max_size) {
  std::map<int, int> stl;
  s21::map<int, int> s21;

  ASSERT_EQ(stl.max_size(), s21.max_size());
}

TEST(map, max_clear_eraze) {
  std::map<std::string, int> stl = {{"one", 1}, {"two", 2}, {"three", 3}};
  s21::map<std::string, int> s21 = {{"one", 1}, {"two", 2}, {"three", 3}};

  stl.erase("two");
  s21.erase("two");
  ASSERT_MAP(stl, s21);
  stl.insert(std::pair<std::string, int>("two", 22));
  s21.insert(std::pair<std::string, int>("two", 22));
  ASSERT_MAP(stl, s21);
  stl.clear();
  s21.clear();
  ASSERT_MAP(stl, s21);
}

TEST(map, swap) {
  std::map<std::string, int> stl_1 = {{"one", 1}, {"three", 3}};
  std::map<std::string, int> stl_2 = {{"two", 2}};

  s21::map<std::string, int> s21_1 = {{"one", 1}, {"three", 3}};
  s21::map<std::string, int> s21_2 = {{"two", 2}};

  stl_1.swap(stl_2);
  s21_1.swap(s21_2);

  ASSERT_MAP(stl_1, s21_1);
}

TEST(map, merge) {
  std::map<std::string, int> stl_1 = {{"one", 1}, {"three", 3}};
  std::map<std::string, int> stl_2 = {{"two", 2}};

  s21::map<std::string, int> s21_1 = {{"one", 1}, {"three", 3}};
  s21::map<std::string, int> s21_2 = {{"two", 2}};

  stl_1.merge(stl_2);
  s21_1.merge(s21_2);

  ASSERT_MAP(stl_1, s21_1);
}

TEST(map, contains) {
  std::map<std::string, int> stl = {
      {"one", 1}, {"two", 1}, {"two", 2}, {"three", 3}};
  s21::map<std::string, int> s21 = {
      {"one", 1}, {"two", 1}, {"two", 2}, {"three", 3}};

  ASSERT_TRUE(s21.contains("two"));
  //  STL Map containts() added in C++20 standart
  ASSERT_EQ(stl.count("two"), 1);
  ASSERT_MAP(stl, s21);
}

TEST(map, insert_or_assign) {
  std::map<std::string, int> stl = {{"one", 1}, {"two", 1}, {"three", 3}};
  s21::map<std::string, int> s21 = {{"one", 1}, {"two", 1}, {"three", 3}};

  stl.insert_or_assign("two", 2);
  s21.insert_or_assign("two", 2);
  ASSERT_MAP(stl, s21);
  stl.insert_or_assign("four", 4);
  s21.insert_or_assign("four", 4);
  ASSERT_MAP(stl, s21);
}

TEST(map, emplace) {
  s21::map<std::string, int> s21 = {{"one", 1}, {"two", 1}, {"three", 3}};
  std::map<std::string, int> stl = {{"one", 1},   {"two", 1},
                                    {"three", 3}, {"seven", 7},
                                    {"six", 6},   {"minus_one", -1}};

  s21.emplace(std::make_pair("seven", 7), std::make_pair("six", 6),
              std::make_pair("minus_one", -1));
  ASSERT_MAP(stl, s21);
  s21.emplace(std::make_pair("nine", 9));
  stl.emplace(std::make_pair("nine", 9));
  ASSERT_MAP(stl, s21);
  s21.emplace(std::make_pair("q", 11), std::make_pair("w", 22),
              std::make_pair("e", 33), std::make_pair("r", 44),
              std::make_pair("t", 55));
  stl.emplace(std::make_pair("q", 11));
  stl.emplace(std::make_pair("w", 22));
  stl.emplace(std::make_pair("e", 33));
  stl.emplace(std::make_pair("r", 44));
  stl.emplace(std::make_pair("t", 55));
  ASSERT_MAP(stl, s21);
  s21.emplace();
  stl.emplace();
  ASSERT_MAP(stl, s21);
  std::pair<std::string, int> val = std::make_pair("w", 22);
  stl.emplace(std::make_pair("qq", 22));
  stl.emplace(val);
  stl.emplace(std::make_pair("ww", 22));
  s21.emplace(std::make_pair("qq", 22), val, std::make_pair("ww", 22));
  ASSERT_MAP(stl, s21);
}

TEST(map, const_iterator) {
  s21::map<int, std::string> s21 = {{1, "one"}, {2, "two"}, {3, "three"}};

  s21::map<int, std::string>::const_iterator it =
      s21::map<int, std::string>::const_iterator(s21.begin());

  ++it;

  ASSERT_EQ((*it).first, 2);
  ASSERT_EQ((*it).second, "two");
}
