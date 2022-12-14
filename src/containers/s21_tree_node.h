#ifndef SRC_S21_TREE_NODE_H_
#define SRC_S21_TREE_NODE_H_

#include <string>

#include "s21_binary_tree.h"

namespace s21 {
template <class Key, class Value>
class BinaryTree;

template <class Key, class Value>
class TreeNode {
  friend BinaryTree<Key, Value>;
  friend typename BinaryTree<Key, Value>::iterator;

 public:
  using value_type = std::pair<Key, Value>;
  using node_type = TreeNode<Key, Value> *;

  TreeNode() {}
  explicit TreeNode(value_type data, node_type nil);

  static node_type copy_tree(const TreeNode<Key, Value> &other,
                             const node_type parent_node, node_type nil_node);
  node_type get_minimum();
  node_type get_maximum();
  std::string to_dot_text();
  std::string color_to_str() { return is_black_ ? "black" : "red"; }
  bool is_nil() const { return !right_ && !left_; }

 private:
  value_type value_;
  bool is_black_ = {true};
  node_type left_ = {nullptr};
  node_type right_ = {nullptr};
  node_type parent_ = {nullptr};
};
}  // namespace s21
#include "s21_tree_node.tpp"

#endif  // SRC_S21_TREE_NODE_H_
