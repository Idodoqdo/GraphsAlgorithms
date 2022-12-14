#include <gtest/gtest.h>

#include <list>

#include "s21_list.h"

auto print = [](auto remark, auto const &container) {
  std::cout << remark;
  for (auto const &val : container) std::cout << ' ' << val;
  std::cout << '\n';
};

template <typename list_my, typename list_lib>
bool eq_list(list_my const L1, list_lib const L2) {
  bool result = true;
  auto iter1 = L1.begin();
  auto iter2 = L2.begin();
  for (; (iter1 != L1.end()) && (iter2 != L2.end()) && result;
       ++iter1, ++iter2) {
    if (*iter1 != *iter2) result = false;
  }
  return result;
}

TEST(list, test_push) {
  std::list<std::string> L1;
  L1.push_front("str1");
  L1.push_back("str2");
  L1.push_back("str3");
  s21::list<std::string> L2;
  L2.push_front("str1");
  L2.push_back("str2");
  L2.push_back("str3");
  ASSERT_EQ(L1.size(), L2.size());
  ASSERT_TRUE(eq_list(L1, L2));
}

TEST(list, test_inizializer) {
  std::list<std::string> L1{"str1", "str2"};
  s21::list<std::string> L2{"str1", "str2"};
  ASSERT_EQ(L1.size(), L2.size());
  ASSERT_TRUE(eq_list(L1, L2));
}

TEST(list, test_erase) {
  std::list<std::string> L1{"str0", "str1", "str2", "str3"};
  s21::list<std::string> L2{"str0", "str1", "str2", "str3"};
  auto iter1 = L1.begin();
  ++iter1;
  L1.erase(iter1);
  auto iter2 = L2.begin();
  ++iter2;
  L2.erase(iter2);
  ASSERT_EQ(L1.size(), L2.size());
  ASSERT_TRUE(eq_list(L1, L2));
}

TEST(list, test_insert) {
  std::list<std::string> L1{"str0", "str1", "str2", "str3"};
  s21::list<std::string> L2{"str0", "str1", "str2", "str3"};
  auto iter1 = L1.begin();
  ++iter1;
  L1.insert(iter1, "tmp");
  auto iter2 = L2.begin();
  ++iter2;
  L2.insert(iter2, "tmp");
  ASSERT_EQ(L1.size(), L2.size());
  ASSERT_TRUE(eq_list(L1, L2));
}

TEST(list, test_insert2) {
  std::list<std::string> L1{"str0", "str1", "str2", "str3"};
  s21::list<std::string> L2{"str0", "str1", "str2", "str3"};
  auto iter1 = L1.end();
  --iter1;
  iter1 = L1.insert(iter1, "tmp");
  auto iter2 = L2.end();
  iter2--;
  iter2++;
  --iter2;
  iter2 = L2.insert(iter2, "tmp");
  ASSERT_TRUE(*iter1 == *iter2);
  ASSERT_EQ(L1.size(), L2.size());
  ASSERT_TRUE(eq_list(L1, L2));
}

TEST(list, test_swap) {
  s21::list<std::string> L1{"str1", "str2"};
  s21::list<std::string> L2{"str3", "str4", "str5"};
  L1.swap(L2);
  std::list<std::string> L3{"str1", "str2"};
  std::list<std::string> L4{"str3", "str4", "str5"};
  L3.swap(L4);
  ASSERT_TRUE(eq_list(L1, L3));
}

TEST(list, test_pop_back) {
  std::list<std::string> L1{"str1", "str2"};
  s21::list<std::string> L2{"str1", "str2"};
  L1.pop_back();
  L2.pop_back();
  ASSERT_EQ(L1.size(), L2.size());
  ASSERT_TRUE(eq_list(L1, L2));
}

TEST(list, test_pop_front) {
  std::list<std::string> L1{"str1", "str2"};
  s21::list<std::string> L2{"str1", "str2"};
  L1.pop_front();
  L2.pop_front();
  ASSERT_EQ(L1.size(), L2.size());
  ASSERT_TRUE(eq_list(L1, L2));
}

TEST(list, test_reverse) {
  std::list<std::string> L1{"str1", "str2"};
  s21::list<std::string> L2{"str1", "str2"};
  L1.reverse();
  L2.reverse();
  ASSERT_TRUE(eq_list(L1, L2));
  ASSERT_EQ(L1.size(), L2.size());
}

TEST(list, test_merge) {
  s21::list<int> L1 = {5, 9, 1, 3, 3};
  s21::list<int> L2 = {8, 7, 2, 3, 4, 4};
  L1.merge(L2);
  std::list<int> list1 = {5, 9, 1, 3, 3};
  std::list<int> list2 = {8, 7, 2, 3, 4, 4};
  list1.merge(list2);
  ASSERT_TRUE(eq_list(L1, list1));
  ASSERT_EQ(L1.size(), list1.size());
}

TEST(list, test_sort) {
  s21::list<int> L1 = {5, 9, 1, 3, 3};
  s21::list<int> L2 = {8, 7, 2, 3, 4, 4};
  L1.sort();
  L2.sort();
  L1.merge(L2);
  std::list<int> list1 = {5, 9, 1, 3, 3};
  std::list<int> list2 = {8, 7, 2, 3, 4, 4};
  list1.sort();
  list2.sort();
  list1.merge(list2);
  ASSERT_TRUE(eq_list(L1, list1));
  ASSERT_EQ(L1.size(), list1.size());
}

TEST(list, test_unique) {
  s21::list<int> L1 = {3, 3, 5, 3, 9, 1, 3, 3};
  L1.unique();
  std::list<int> L2 = {3, 3, 5, 3, 9, 1, 3, 3};
  L2.unique();
  ASSERT_TRUE(eq_list(L1, L2));
  ASSERT_EQ(L1.size(), L2.size());
}

TEST(list, test_splice) {
  s21::list<int> L1 = {5, 9, 1, 3, 3};
  s21::list<int> L2 = {8, 7, 2, 3, 4, 4};
  auto iter = L1.begin();
  ++iter;
  L1.splice(iter, L2);
  std::list<int> list1 = {5, 9, 1, 3, 3};
  std::list<int> list2 = {8, 7, 2, 3, 4, 4};
  auto iter3 = list1.begin();
  ++iter3;
  list1.splice(iter3, list2);
  ASSERT_TRUE(eq_list(L1, list1));
  ASSERT_EQ(L1.size(), list1.size());
}

TEST(list, test_max_size) {
  s21::list<std::string> list1;
  std::list<std::string> list2;
  ASSERT_EQ(list1.max_size(), list2.max_size());
}

TEST(list, test_constructor1) {
  s21::list<std::string> L1({"str1", "str2", "str3"});
  s21::list<std::string> L2({"str1", "str2", "str3"});
  s21::list<std::string> L4 = std::move(L2);
  ASSERT_TRUE(eq_list(L1, L4));
  L2 = std::move(L4);
  ASSERT_TRUE(eq_list(L1, L2));
}

TEST(list, test_constructor2) {
  s21::list<std::string> L3(2);
  std::list<std::string> L5(2);
  ASSERT_EQ(L3.size(), L5.size());
  ASSERT_TRUE(eq_list(L3, L5));
}

TEST(list, test_iterator) {
  s21::list<std::string> L1({"str1", "str2", "str3"});
  auto iter1 = L1.begin();
  auto iter2 = L1.begin();
  ASSERT_TRUE(iter1 == iter2);
}

TEST(list, test_front_back) {
  std::list<std::string> L1({"str1", "str2", "str3"});
  s21::list<std::string> L2({"str1", "str2", "str3"});
  ASSERT_TRUE(L1.front() == L2.front());
  ASSERT_TRUE(L1.back() == L2.back());
}

TEST(list, test_emplace_front) {
  std::list<std::string> Q1({"str1", "str2", "str3"});
  s21::list<std::string> Q2({"str1", "str2", "str3"});
  std::string S = "tmp";
  Q1.emplace_front(S);
  Q2.emplace_front(S);
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_list(Q1, Q2));
  Q1.emplace_front("tmp2");
  Q2.emplace_front("tmp2");
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_list(Q1, Q2));
  Q1.emplace_front(S);
  Q1.emplace_front("tmp4");
  Q1.emplace_front("tmp4");
  Q2.emplace_front(S, "tmp4", "tmp4");
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_list(Q1, Q2));
}

TEST(list, test_emplace_back) {
  std::list<std::string> Q1({"str1", "str2", "str3"});
  s21::list<std::string> Q2({"str1", "str2", "str3"});
  std::string S = "tmp";
  Q1.emplace_back(S);
  Q2.emplace_back(S);
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_list(Q1, Q2));
  Q1.emplace_back("tmp2");
  Q2.emplace_back("tmp2");
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_list(Q1, Q2));
  Q1.emplace_back(S);
  Q1.emplace_back("tmp4");
  Q1.emplace_back("tmp4");
  Q2.emplace_back(S, "tmp4", "tmp4");
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_list(Q1, Q2));
}

TEST(list, test_emplace) {
  std::list<std::string> Q1({"str1", "str2", "str3"});
  s21::list<std::string> Q2({"str1", "str2", "str3"});
  std::string S = "tmp";
  auto iter1 = Q1.begin();
  ++iter1;
  auto iter2 = Q2.begin();
  ++iter2;
  Q1.emplace(iter1, S);
  Q2.emplace(iter2, S);
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_list(Q1, Q2));
  Q1.emplace(iter1, "tmp2");
  Q2.emplace(iter2, "tmp2");
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_list(Q1, Q2));
  Q1.emplace(iter1, S);
  Q1.emplace(iter1, "tmp4");
  Q1.emplace(iter1, "tmp4");
  Q2.emplace(iter2, S, "tmp4", "tmp4");
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_list(Q1, Q2));
}

TEST(list, test_emplace_front_0_5) {
  std::list<std::string> Q1({"str1", "str2", "str3"});
  s21::list<std::string> Q2({"str1", "str2", "str3"});
  std::string S = "tmp";
  Q1.emplace_front();
  Q2.emplace_front();
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_list(Q1, Q2));
  Q1.emplace_front("tmp");
  Q1.emplace_front("tmp1");
  Q1.emplace_front("tmp2");
  Q1.emplace_front("tmp3");
  Q1.emplace_front("tmp4");
  Q2.emplace_front(S, "tmp1", "tmp2", "tmp3", "tmp4");
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_list(Q1, Q2));
}

TEST(list, test_emplace_back_0_5) {
  std::list<std::string> Q1({"str1", "str2", "str3"});
  s21::list<std::string> Q2({"str1", "str2", "str3"});
  std::string S = "tmp";
  Q1.emplace_back();
  Q2.emplace_back();
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_list(Q1, Q2));
  Q1.emplace_back("tmp");
  Q1.emplace_back("tmp1");
  Q1.emplace_back("tmp2");
  Q1.emplace_back("tmp3");
  Q1.emplace_back("tmp4");
  Q2.emplace_back(S, "tmp1", "tmp2", "tmp3", "tmp4");
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_list(Q1, Q2));
}

TEST(list, test_emplace_0_5) {
  std::list<std::string> Q1({"str1", "str2", "str3"});
  s21::list<std::string> Q2({"str1", "str2", "str3"});
  auto iter1 = Q1.begin();
  ++iter1;
  auto iter2 = Q2.begin();
  ++iter2;
  std::string S;
  Q1.emplace(iter1, S);
  Q2.emplace(iter2, S);
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_list(Q1, Q2));
  Q1.emplace(iter1, S);
  Q1.emplace(iter1, "tmp1");
  Q1.emplace(iter1, "tmp2");
  Q1.emplace(iter1, "tmp3");
  Q1.emplace(iter1, "tmp4");
  Q2.emplace(iter2, S, "tmp1", "tmp2", "tmp3", "tmp4");
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_list(Q1, Q2));
}

TEST(list, exceptions) {
  s21::list<std::string> Q2;
  EXPECT_THROW({ Q2.pop_back(); }, std::invalid_argument);
  EXPECT_THROW({ Q2.pop_front(); }, std::invalid_argument);
}
