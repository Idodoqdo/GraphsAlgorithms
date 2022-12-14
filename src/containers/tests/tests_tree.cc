// Copyright <jgerrick, kmodesta, lwolmer, tfelton> 2022
#include <gtest/gtest.h>

#include <map>
#include <string>

#include "s21_binary_tree.h"

template <class key, class value>
void ASSERT_TREE(s21::BinaryTree<key, value> tree, std::map<key, value> raw) {
  typename s21::BinaryTree<key, value>::iterator tree_it = tree.begin();
  typename std::map<key, value>::iterator raw_it = raw.begin();

  ASSERT_EQ(tree.get_size(), raw.size());
  while (tree_it != tree.end() && raw_it != raw.end()) {
    ASSERT_EQ((*tree_it).first, raw_it->first);
    ASSERT_EQ((*tree_it).second, raw_it->second);
    ++tree_it;
    ++raw_it;
  }
  ASSERT_TRUE(tree_it == tree.end() && raw_it == raw.end());
}

template <class key, class value>
void ASSERT_TREE_NE(s21::BinaryTree<key, value> tree,
                    std::map<key, value> raw) {
  typename s21::BinaryTree<key, value>::iterator tree_it = tree.begin();
  typename std::map<key, value>::iterator raw_it = raw.begin();
  bool not_equal = true;
  while (tree_it != tree.end() && raw_it != raw.end() && not_equal) {
    if ((*tree_it).first == raw_it->first ||
        (*tree_it).second == raw_it->second)
      not_equal = false;
    ++tree_it;
    ++raw_it;
  }
  ASSERT_TRUE(not_equal);
}

template <class key, class value>
void ASSERT_TREE_MULTI(s21::BinaryTree<key, value> tree,
                       std::multiset<key> raw) {
  typename s21::BinaryTree<key, value>::iterator tree_it = tree.begin();
  typename std::multiset<key>::iterator raw_it = raw.begin();

  ASSERT_EQ(tree.get_size(), raw.size());
  while (tree_it != tree.end() && raw_it != raw.end()) {
    ASSERT_EQ((*tree_it).first, *raw_it);
    ++tree_it;
    ++raw_it;
  }
  ASSERT_TRUE(tree_it == tree.end() && raw_it == raw.end());
}

TEST(binary_tree, constructor_default) {
  s21::BinaryTree<std::string, int> tree_1;
  ASSERT_EQ(tree_1.get_size(), 0);
  ASSERT_EQ(tree_1.begin(), tree_1.end());

  tree_1.insert_node(std::make_pair("one", 1), false);
  tree_1.insert_node(std::make_pair("three", 3), false);
  tree_1.insert_node(std::make_pair("two", 2), false);
  std::map<std::string, int> map_test =
      std::map<std::string, int>{{"one", 1}, {"two", 2}, {"three", 3}};
  ASSERT_TREE(tree_1, map_test);
}

TEST(binary_tree, constructor_copy) {
  s21::BinaryTree<std::string, int> tree_1;
  tree_1.insert_node(std::make_pair("one", 1), false);
  tree_1.insert_node(std::make_pair("three", 3), false);
  tree_1.insert_node(std::make_pair("two", 2), false);
  std::map<std::string, int> map_test =
      std::map<std::string, int>{{"one", 1}, {"two", 2}, {"three", 3}};
  s21::BinaryTree<std::string, int> tree_copy =
      s21::BinaryTree<std::string, int>(tree_1);
  ASSERT_TREE(tree_copy, map_test);
}

TEST(binary_tree, constructor_move) {
  s21::BinaryTree<std::string, int> tree_1;

  tree_1.insert_node(std::make_pair("one", 1), false);
  tree_1.insert_node(std::make_pair("three", 3), false);
  tree_1.insert_node(std::make_pair("two", 2), false);
  std::map<std::string, int> map_test =
      std::map<std::string, int>{{"one", 1}, {"two", 2}, {"three", 3}};
  ASSERT_TREE(tree_1, map_test);
  s21::BinaryTree<std::string, int> tree_move = std::move(tree_1);
  ASSERT_TREE(tree_move, map_test);
}

TEST(binary_tree, move_operator) {
  s21::BinaryTree<std::string, int> tree_1;

  tree_1.insert_node(std::make_pair("one", 1), false);
  tree_1.insert_node(std::make_pair("three", 3), false);
  tree_1.insert_node(std::make_pair("two", 2), false);
  std::map<std::string, int> map_test =
      std::map<std::string, int>{{"one", 1}, {"two", 2}, {"three", 3}};
  ASSERT_TREE(tree_1, map_test);

  s21::BinaryTree<std::string, int> tree_move;
  tree_move = std::move(tree_1);
  ASSERT_TREE(tree_move, map_test);
}

TEST(binary_tree, assign_operator) {
  s21::BinaryTree<std::string, int> tree;
  s21::BinaryTree<std::string, int> tree_copy;
  tree_copy = tree;

  tree.insert_node(std::make_pair("one", 1), false);
  tree.insert_node(std::make_pair("three", 3), false);
  tree.insert_node(std::make_pair("two", 2), false);
  std::map<std::string, int> map_test =
      std::map<std::string, int>{{"one", 1}, {"two", 2}, {"three", 3}};
  ASSERT_TREE(tree, map_test);

  tree_copy = tree;
  ASSERT_TREE(tree_copy, map_test);

  auto tree_it = tree.begin();
  s21::BinaryTree<std::string, int>::iterator it_copy;
  it_copy = tree_it;
  ASSERT_TRUE(it_copy == tree_it);
}

TEST(binary_tree, iterator_backwards) {
  s21::BinaryTree<std::string, int> tree;

  tree.insert_node(std::make_pair("one", 1), false);
  tree.insert_node(std::make_pair("three", 3), false);
  tree.insert_node(std::make_pair("two", 2), false);
  tree.insert_node(std::make_pair("seven", 7), false);
  tree.insert_node(std::make_pair("five", 5), false);
  tree.insert_node(std::make_pair("six", 6), false);
  tree.insert_node(std::make_pair("four", 4), false);
  tree.insert_node(std::make_pair("eight", 8), false);
  tree.insert_node(std::make_pair("nine", 9), false);
  std::map<std::string, int> map_test = std::map<std::string, int>{
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  auto tree_it = tree.end();
  auto raw_it = map_test.end();
  ASSERT_EQ(tree.get_size(), map_test.size());
  do {
    --tree_it;
    --raw_it;
    ASSERT_EQ((*tree_it).first, raw_it->first);
    ASSERT_EQ((*tree_it).second, raw_it->second);
  } while (tree_it != tree.begin() && raw_it != map_test.begin());
  ASSERT_TRUE(tree_it == tree.begin() && raw_it == map_test.begin());
}

TEST(binary_tree, iterator_forwards) {
  s21::BinaryTree<std::string, int> tree;

  tree.insert_node(std::make_pair("one", 1), false);
  tree.insert_node(std::make_pair("three", 3), false);
  tree.insert_node(std::make_pair("two", 2), false);
  tree.insert_node(std::make_pair("seven", 7), false);
  tree.insert_node(std::make_pair("five", 5), false);
  tree.insert_node(std::make_pair("six", 6), false);
  tree.insert_node(std::make_pair("four", 4), false);
  tree.insert_node(std::make_pair("eight", 8), false);
  tree.insert_node(std::make_pair("nine", 9), false);
  std::map<std::string, int> map_test = std::map<std::string, int>{
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  auto tree_it = tree.begin();
  auto raw_it = map_test.begin();
  ASSERT_EQ(tree.get_size(), map_test.size());
  while (tree_it != tree.end() && raw_it != map_test.end()) {
    ASSERT_EQ((*tree_it).first, raw_it->first);
    ASSERT_EQ((*tree_it).second, raw_it->second);
    ++tree_it;
    ++raw_it;
  }
  ASSERT_TRUE(tree_it == tree.end() && raw_it == map_test.end());
}

TEST(binary_tree, insert_erase) {
  s21::BinaryTree<std::string, int> tree;

  tree.insert_node(std::make_pair("one", 1), false);
  tree.insert_node(std::make_pair("three", 3), false);
  tree.insert_node(std::make_pair("two", 2), false);
  std::map<std::string, int> map_test =
      std::map<std::string, int>{{"one", 1}, {"three", 3}};
  tree.erase_node(tree.find("two").first);
  ASSERT_TREE(tree, map_test);
  tree.insert_node(std::make_pair("five", 5), false);
  tree.insert_node(std::make_pair("nine", 9), false);
  std::map<std::string, int> map_test2 = std::map<std::string, int>{
      {"one", 1}, {"three", 3}, {"five", 5}, {"nine", 9}};
  ASSERT_TREE(tree, map_test2);
  tree.erase_node(tree.find("five").first);
  tree.erase_node(tree.find("nine").first);
  ASSERT_TREE(tree, map_test);
  tree.erase_node(tree.find("one").first);
  tree.erase_node(tree.find("three").first);
  ASSERT_EQ(tree.get_size(), 0);
}

TEST(binary_tree, expect_fail) {
  s21::BinaryTree<std::string, int> tree;

  tree.insert_node(std::make_pair("one", 1), false);
  tree.insert_node(std::make_pair("three", 3), false);
  tree.insert_node(std::make_pair("two", 2), false);
  std::map<std::string, int> map_test = std::map<std::string, int>{
      {"one", 1}, {"three", 3}, {"five", 5}, {"nine", 9}};
  ASSERT_TREE_NE(tree, map_test);
}

TEST(binary_tree, insert_erase_2) {
  s21::BinaryTree<int, std::string> tree;

  tree.insert_node(std::make_pair(15, "fifteen"), false);
  tree.insert_node(std::make_pair(9, "nine"), false);
  tree.insert_node(std::make_pair(3, "three"), false);
  tree.insert_node(std::make_pair(11, "eleven"), false);
  tree.insert_node(std::make_pair(6, "six"), false);
  tree.insert_node(std::make_pair(1, "one"), false);
  tree.insert_node(std::make_pair(5, "five"), false);
  tree.insert_node(std::make_pair(16, "sixteen"), false);
  tree.insert_node(std::make_pair(2, "two"), false);
  tree.insert_node(std::make_pair(13, "thirteen"), false);
  tree.insert_node(std::make_pair(12, "twelve"), false);
  tree.insert_node(std::make_pair(4, "four"), false);
  tree.insert_node(std::make_pair(14, "fourteen"), false);
  tree.insert_node(std::make_pair(7, "seven"), false);
  tree.insert_node(std::make_pair(8, "eight"), false);
  tree.insert_node(std::make_pair(10, "ten"), false);

  std::map<int, std::string> map_test = std::map<int, std::string>{
      {1, "one"},       {2, "two"},       {3, "three"},    {4, "four"},
      {5, "five"},      {6, "six"},       {7, "seven"},    {8, "eight"},
      {9, "nine"},      {10, "ten"},      {11, "eleven"},  {12, "twelve"},
      {13, "thirteen"}, {14, "fourteen"}, {15, "fifteen"}, {16, "sixteen"}};
  ASSERT_TREE(tree, map_test);

  tree.erase_node(tree.find(15).first);
  tree.insert_node(std::make_pair(15, "fifteen"), false);
  ASSERT_TREE(tree, map_test);

  tree.erase_node(tree.find(11).first);
  tree.insert_node(std::make_pair(11, "eleven"), false);
  ASSERT_TREE(tree, map_test);

  tree.erase_node(tree.find(12).first);
  tree.insert_node(std::make_pair(12, "twelve"), false);
  ASSERT_TREE(tree, map_test);

  tree.erase_node(tree.find(16).first);
  tree.insert_node(std::make_pair(16, "sixteen"), false);
  ASSERT_TREE(tree, map_test);

  tree.erase_node(tree.find(1).first);
  tree.erase_node(tree.find(2).first);
  tree.insert_node(std::make_pair(1, "one"), false);
  tree.insert_node(std::make_pair(2, "two"), false);
  ASSERT_TREE(tree, map_test);

  tree.insert_node(std::make_pair(8, "eight"), false);
  ASSERT_TREE(tree, map_test);
}

TEST(binary_tree, insert_erase_reps) {
  s21::BinaryTree<int, char> tree;

  tree.insert_node(std::make_pair(9, 0), true);
  tree.insert_node(std::make_pair(3, 0), true);
  tree.insert_node(std::make_pair(1, 0), true);
  tree.insert_node(std::make_pair(3, 0), true);
  tree.insert_node(std::make_pair(2, 0), true);
  tree.insert_node(std::make_pair(3, 0), true);
  tree.insert_node(std::make_pair(4, 0), true);
  tree.insert_node(std::make_pair(7, 0), true);
  std::multiset<int> multiset_test = std::multiset<int>{9, 3, 1, 3, 2, 3, 4, 7};
  ASSERT_TREE_MULTI(tree, multiset_test);
  tree.erase_node(tree.find(2).first);
  tree.insert_node(std::make_pair(2, 0), true);
  ASSERT_TREE_MULTI(tree, multiset_test);

  tree.erase_node(tree.find(3).first);
  tree.insert_node(std::make_pair(3, 0), true);
  ASSERT_TREE_MULTI(tree, multiset_test);

  tree.insert_node(std::make_pair(9, 0), false);
  ASSERT_TREE_MULTI(tree, multiset_test);
}