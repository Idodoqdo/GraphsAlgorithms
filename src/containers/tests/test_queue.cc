// Copyright <jgerrick, kmodesta, lwolmer, tfelton> 2022
#include <gtest/gtest.h>

#include <queue>

#include "s21_queue.h"

template <typename Queue>
void print(Queue queue, int id) {
  std::cout << "s" << id << " [" << queue.size() << "]: ";
  for (; !queue.empty(); queue.pop()) std::cout << queue.front() << ' ';
  std::cout << (id > 1 ? "\n\n" : "\n");
}

template <typename queue_my, typename queue_lib>
bool eq_queue(queue_my my_queue, queue_lib lib_queue) {
  bool result = true;
  for (; !my_queue.empty() || !lib_queue.empty();
       my_queue.pop(), lib_queue.pop()) {
    if (my_queue.front() != lib_queue.front()) result = false;
  }
  return result;
}

TEST(queue, test_construct) {
  std::queue<std::string> Q1({"str1", "str2", "str3"});
  s21::queue<std::string> Q2({"str1", "str2", "str3"});
  ASSERT_EQ(Q1.back(), Q2.back());
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_queue(Q1, Q2));
  s21::queue<std::string> Q4 = std::move(Q2);
  ASSERT_TRUE(eq_queue(Q1, Q4));
  Q2 = std::move(Q4);
  ASSERT_TRUE(eq_queue(Q1, Q2));
}

TEST(queue, test_pop) {
  std::queue<std::string> Q1({"str1", "str2", "str3"});
  s21::queue<std::string> Q2({"str1", "str2", "str3"});
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_TRUE(eq_queue(Q1, Q2));
  Q2.pop();
  Q2.pop();
  Q1.pop();
  Q1.pop();
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  Q1.push("str1");
  Q2.push("str1");
  ASSERT_TRUE(eq_queue(Q1, Q2));
}

TEST(queue, test_swap) {
  std::queue<std::string> Q1;
  Q1.push("str1");
  Q1.push("str2");
  std::queue<std::string> Q3;
  Q3.push("str3");
  Q3.push("str4");
  s21::queue<std::string> Q2;
  Q2.push("str1");
  Q2.push("str2");
  s21::queue<std::string> Q4;
  Q4.push("str3");
  Q4.push("str4");
  Q1.swap(Q3);
  Q2.swap(Q4);
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_queue(Q1, Q2));
}

TEST(queue, test_emplace) {
  std::queue<std::string> Q1({"str1", "str2", "str3"});
  s21::queue<std::string> Q2({"str1", "str2", "str3"});
  std::string S = "tmp";
  Q1.emplace(S);
  Q2.emplace_back(S);
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_queue(Q1, Q2));
  Q1.emplace("tmp2");
  Q2.emplace_back("tmp2");
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_queue(Q1, Q2));
  Q1.emplace("tmp");
  Q1.emplace("tmp4");
  Q1.emplace("tmp4");
  Q2.emplace_back(S, "tmp4", "tmp4");
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_queue(Q1, Q2));
}

TEST(queue, test_emplace_0_5) {
  std::queue<std::string> Q1({"str1", "str2", "str3"});
  s21::queue<std::string> Q2({"str1", "str2", "str3"});
  std::string S = "tmp";
  Q1.emplace();
  Q2.emplace_back();
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_queue(Q1, Q2));
  Q1.emplace("tmp");
  Q1.emplace("tmp1");
  Q1.emplace("tmp2");
  Q1.emplace("tmp3");
  Q1.emplace("tmp4");
  Q2.emplace_back(S, "tmp1", "tmp2", "tmp3", "tmp4");
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_queue(Q1, Q2));
}

TEST(queue, exception) {
  s21::queue<std::string> Q2;
  EXPECT_THROW({ Q2.pop(); }, std::invalid_argument);
}
