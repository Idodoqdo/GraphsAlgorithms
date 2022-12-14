// Copyright <jgerrick, kmodesta, lwolmer, tfelton> 2022
#include <gtest/gtest.h>

#include <stack>

#include "s21_stack.h"

template <typename Stack>
void print(Stack stack, int id) {
  std::cout << "s" << id << " [" << stack.size() << "]: ";
  for (; !stack.empty(); stack.pop()) std::cout << stack.top() << ' ';
  std::cout << (id > 1 ? "\n\n" : "\n");
}

template <typename stack_my, typename stack_lib>
bool eq_stack(stack_my my_stack, stack_lib lib_stack) {
  bool result = true;
  for (; !my_stack.empty() || !lib_stack.empty();
       my_stack.pop(), lib_stack.pop()) {
    if (my_stack.top() != lib_stack.top()) result = false;
  }
  return result;
}

TEST(stack, test_pop) {
  std::stack<std::string> S1({"str1", "str2", "str3"});
  s21::stack<std::string> S2({"str1", "str2", "str3"});
  ASSERT_EQ(S1.size(), S2.size());
  ASSERT_TRUE(eq_stack(S1, S2));
  S2.pop();
  S2.pop();
  S1.pop();
  S1.pop();
  ASSERT_EQ(S1.size(), S2.size());
  ASSERT_EQ(S1.empty(), S2.empty());
  S1.push("str1");
  S2.push("str1");
  ASSERT_TRUE(eq_stack(S1, S2));
  s21::stack<std::string> S4 = std::move(S2);
  ASSERT_TRUE(eq_stack(S1, S4));
  S2 = std::move(S4);
  ASSERT_TRUE(eq_stack(S1, S2));
}

TEST(stack, test_swap) {
  std::stack<std::string> S1;
  S1.push("str1");
  S1.push("str2");
  std::stack<std::string> S3;
  S3.push("str3");
  S3.push("str4");
  s21::stack<std::string> S2;
  S2.push("str1");
  S2.push("str2");
  s21::stack<std::string> S4;
  S4.push("str3");
  S4.push("str4");
  S1.swap(S3);
  S2.swap(S4);
  ASSERT_EQ(S1.size(), S2.size());
  ASSERT_EQ(S1.empty(), S2.empty());
  ASSERT_TRUE(eq_stack(S1, S2));
}

TEST(stack, test_emplace) {
  std::stack<std::string> Q1({"str1", "str2", "str3"});
  s21::stack<std::string> Q2({"str1", "str2", "str3"});
  std::string S = "tmp";
  Q1.emplace(S);
  Q2.emplace_front(S);
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_stack(Q1, Q2));
  Q1.emplace("tmp2");
  Q2.emplace_front("tmp2");
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_stack(Q1, Q2));
  Q1.emplace(S);
  Q1.emplace("tmp4");
  Q1.emplace("tmp4");
  Q2.emplace_front(S, "tmp4", "tmp4");
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_stack(Q1, Q2));
}

TEST(stack, test_emplace_0_5) {
  std::stack<std::string> Q1({"str1", "str2", "str3"});
  s21::stack<std::string> Q2({"str1", "str2", "str3"});
  std::string S = "tmp";
  Q1.emplace();
  Q2.emplace_front();
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_stack(Q1, Q2));
  Q1.emplace("tmp");
  Q1.emplace("tmp1");
  Q1.emplace("tmp2");
  Q1.emplace("tmp3");
  Q1.emplace("tmp4");
  Q2.emplace_front(S, "tmp1", "tmp2", "tmp3", "tmp4");
  ASSERT_EQ(Q1.size(), Q2.size());
  ASSERT_EQ(Q1.empty(), Q2.empty());
  ASSERT_TRUE(eq_stack(Q1, Q2));
}

TEST(stack, exception) {
  s21::stack<std::string> Q2;
  EXPECT_THROW({ Q2.pop(); }, std::invalid_argument);
}
