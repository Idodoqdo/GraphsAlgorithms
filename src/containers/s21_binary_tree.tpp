// Copyright <jgerrick, kmodesta, lwolmer, tfelton> 2022
#ifndef SRC_S21_BINARY_TREE_TPP_
#define SRC_S21_BINARY_TREE_TPP_
#include "s21_binary_tree.h"

namespace s21 {
template <class Key, class Value>
BinaryTree<Key, Value>::BinaryTree() : size_(0) {
  nil_ = new TreeNode<Key, Value>;
  root_ = nil_;
}

template <class Key, class Value>
BinaryTree<Key, Value>::BinaryTree(const BinaryTree &other)
    : size_(other.size_) {
  nil_ = new TreeNode<Key, Value>;
  root_ = TreeNode<Key, Value>::copy_tree(*other.root_, nullptr, nil_);
}

template <class Key, class Value>
BinaryTree<Key, Value>::BinaryTree(BinaryTree &&other) : size_(other.size_) {
  nil_ = other.nil_;
  root_ = other.root_;
  other.nil_ = nullptr;
  other.root_ = nullptr;
}

template <class Key, class Value>
BinaryTree<Key, Value>::~BinaryTree() {
  if (root_ && !root_->is_nil()) {
    clear_tree(root_);
  }
  delete nil_;
}

template <class Key, class Value>
void BinaryTree<Key, Value>::clear_tree(node_type node) {
  if (node == nil_) return;
  if (!node->right_->is_nil()) {
    clear_tree(node->right_);
  }
  if (!node->left_->is_nil()) {
    clear_tree(node->left_);
  }
  if (!node->is_nil()) {
    if (node == root_) {
      root_ = nil_;
    }
    delete node;
    size_--;
  }
}

template <class Key, class Value>
BinaryTree<Key, Value> &BinaryTree<Key, Value>::operator=(
    const BinaryTree &other) {
  if (this != &other) {
    if (root_) clear_tree(root_);
    delete nil_;
    nil_ = new TreeNode<Key, Value>;
    size_ = other.size_;
    root_ = TreeNode<Key, Value>::copy_tree(*other.root_, nullptr, nil_);
  }
  return *this;
}

template <class Key, class Value>
BinaryTree<Key, Value> &BinaryTree<Key, Value>::operator=(BinaryTree &&other) {
  if (this != &other) {
    if (root_) clear_tree(root_);
    delete nil_;
    size_ = other.size_;
    nil_ = other.nil_;
    root_ = other.root_;
    other.root_ = nullptr;
    other.nil_ = nullptr;
  }
  return *this;
}

template <class Key, class Value>
BinaryTree<Key, Value>::iterator::iterator() : node_(nullptr) {}

template <class Key, class Value>
BinaryTree<Key, Value>::iterator::iterator(node_type node) {
  node_ = node;
}

template <class Key, class Value>
BinaryTree<Key, Value>::iterator::iterator(const iterator &other)
    : node_(other.node_) {}

template <class Key, class Value>
BinaryTree<Key, Value>::iterator::iterator(iterator &&other) {
  node_ = other.node_;
  other.node_ = nullptr;
}

template <class Key, class Value>
typename BinaryTree<Key, Value>::iterator &BinaryTree<Key, Value>::iterator::
operator=(const iterator &other) {
  if (this != &other) {
    node_ = other.node_;
  }
  return *this;
}

template <class Key, class Value>
typename BinaryTree<Key, Value>::iterator &BinaryTree<Key, Value>::iterator::
operator=(iterator &&other) {
  if (this != &other) {
    node_ = other.node_;
    other.node_ = nullptr;
  }
  return *this;
}

template <class Key, class Value>
typename BinaryTree<Key, Value>::iterator &BinaryTree<Key, Value>::iterator::
operator++() {
  node_type next;
  if (!node_->right_->is_nil()) {
    next = node_->right_->get_minimum();
  } else if (node_->right_->parent_ == node_) {
    next = node_->right_;
  } else {
    next = node_->parent_;
    while (next && node_ == next->right_) {
      node_ = next;
      next = node_->parent_;
    }
  }
  node_ = next;
  return *this;
}

template <class Key, class Value>
typename BinaryTree<Key, Value>::iterator &BinaryTree<Key, Value>::iterator::
operator--() {
  node_type prev;
  if (node_->is_nil()) {
    prev = node_->parent_;
  } else if (!node_->left_->is_nil()) {
    prev = node_->left_->get_maximum();
  } else {
    prev = node_->parent_;
    while (prev && node_ == prev->left_) {
      node_ = prev;
      prev = node_->parent_;
    }
  }
  node_ = prev;
  return *this;
}

template <class Key, class Value>
std::pair<typename BinaryTree<Key, Value>::iterator, bool>
BinaryTree<Key, Value>::find(const key_type &key) {
  node_type node = root_;
  bool success = true;
  while (!node->is_nil() && key != node->value_.first) {
    if (key < node->value_.first) {
      node = node->left_;
    } else {
      node = node->right_;
    }
  }
  if (node->is_nil()) {
    success = false;
  }
  return std::make_pair(iterator(node), success);
}

template <class Key, class Value>
std::pair<typename BinaryTree<Key, Value>::iterator, bool>
BinaryTree<Key, Value>::insert_node(const std::pair<Key, Value> &value,
                                    bool is_repeatable) {
  std::pair<typename BinaryTree<Key, Value>::iterator, bool> result;
  if (!is_repeatable && find(value.first).second) {
    result = std::make_pair(iterator(nil_), false);
  } else {
    node_type new_node = new TreeNode<Key, Value>(value, nil_);
    naive_insert(new_node);
    balance_tree_after_insertion(new_node);
    size_++;
    result = std::make_pair(iterator(new_node), true);
  }
  return result;
}

template <class Key, class Value>
void BinaryTree<Key, Value>::naive_insert(node_type node) {
  node_type child = root_;
  node_type parent = nullptr;
  while (!child->is_nil()) {
    parent = child;
    if (node->value_.first < child->value_.first) {
      child = child->left_;
    } else {
      child = child->right_;
    }
  }
  node->parent_ = parent;
  if (!parent) {
    root_ = node;
  } else if (node->value_.first < parent->value_.first) {
    parent->left_ = node;
  } else {
    parent->right_ = node;
  }
}

template <class Key, class Value>
void BinaryTree<Key, Value>::balance_tree_after_insertion(node_type node) {
  node->is_black_ = false;
  while (node != root_ && !node->parent_->is_black_) {
    if (node->parent_ == node->parent_->parent_->left_) {
      case_parent_left(node);
    } else {
      case_parent_right(node);
    }
  }
  nil_->parent_ = root_->get_maximum();
  root_->is_black_ = true;
}

template <class Key, class Value>
void BinaryTree<Key, Value>::case_parent_left(node_type &node) {
  node_type uncle = node->parent_->parent_->right_;
  if (!uncle->is_black_) {
    change_colors_one(node, uncle);
    node = node->parent_->parent_;
  } else {
    if (node == node->parent_->right_) {
      node = node->parent_;
      rotate_left(node);
    }
    change_colors_two(node->parent_, node->parent_->parent_);
    rotate_right(node->parent_->parent_);
  }
}

template <class Key, class Value>
void BinaryTree<Key, Value>::case_parent_right(node_type &node) {
  node_type uncle = node->parent_->parent_->left_;
  if (!uncle->is_black_) {
    change_colors_one(node, uncle);
    node = node->parent_->parent_;
  } else {
    if (node == node->parent_->left_) {
      node = node->parent_;
      rotate_right(node);
    }
    change_colors_two(node->parent_, node->parent_->parent_);
    rotate_left(node->parent_->parent_);
  }
}

template <class Key, class Value>
inline void BinaryTree<Key, Value>::change_colors_one(node_type child,
                                                      node_type uncle) {
  child->parent_->is_black_ = true;
  uncle->is_black_ = true;
  child->parent_->parent_->is_black_ = false;
}

template <class Key, class Value>
inline void BinaryTree<Key, Value>::change_colors_two(node_type one,
                                                      node_type two) {
  one->is_black_ = true;
  two->is_black_ = false;
}

template <class Key, class Value>
void BinaryTree<Key, Value>::rotate_right(node_type node_x) {
  node_type node_y = node_x->left_;
  node_x->left_ = node_y->right_;
  if (!node_y->right_->is_nil()) {
    node_y->right_->parent_ = node_x;
  }
  connect_to_parent(node_x, node_y);
  node_y->right_ = node_x;
  node_x->parent_ = node_y;
}

template <class Key, class Value>
void BinaryTree<Key, Value>::rotate_left(node_type node_x) {
  node_type node_y = node_x->right_;
  node_x->right_ = node_y->left_;
  if (!node_y->left_->is_nil()) {
    node_y->left_->parent_ = node_x;
  }
  connect_to_parent(node_x, node_y);
  node_y->left_ = node_x;
  node_x->parent_ = node_y;
}

template <class Key, class Value>
void BinaryTree<Key, Value>::connect_to_parent(node_type one, node_type two) {
  two->parent_ = one->parent_;
  if (one->parent_ == nullptr) {
    root_ = two;
  } else if (one == one->parent_->left_) {
    one->parent_->left_ = two;
  } else {
    one->parent_->right_ = two;
  }
}

template <class Key, class Value>
void BinaryTree<Key, Value>::erase_node(iterator pos) {
  iterator child;
  iterator to_erase = pos;
  if (!(pos.node_->left_->is_nil() || pos.node_->right_->is_nil())) {
    ++to_erase;
  }
  if (!to_erase.node_->left_->is_nil()) {
    child = iterator(to_erase.node_->left_);
  } else {
    child = iterator(to_erase.node_->right_);
  }
  connect_to_parent(to_erase.node_, child.node_);
  if (to_erase != pos) {
    pos.node_->value_ = to_erase.node_->value_;
  }
  if (to_erase.node_->is_black_) {
    balance_tree_after_erasure(child.node_);
  }
  delete to_erase.node_;
  size_--;
}

template <class Key, class Value>
void BinaryTree<Key, Value>::balance_tree_after_erasure(node_type node) {
  while (node != root_ && node->is_black_) {
    if (node == node->parent_->left_) {
      case_node_left(node);
    } else if (node == node->parent_->right_) {
      case_node_right(node);
    }
  }
  nil_->parent_ = root_->get_maximum();
  node->is_black_ = true;
}

template <class Key, class Value>
void BinaryTree<Key, Value>::case_node_left(node_type &node) {
  node_type brother = node->parent_->right_;
  if (!brother->is_black_) {
    change_colors_two(brother, node->parent_);
    rotate_left(node->parent_);
    brother = node->parent_->right_;
  }
  if (brother->left_->is_black_ && brother->right_->is_black_) {
    brother->is_black_ = false;
    node = node->parent_;
  } else {
    if (brother->right_->is_black_) {
      change_colors_two(brother->left_, brother);
      rotate_right(brother);
      brother = node->parent_->right_;
    }
    brother->is_black_ = node->parent_->is_black_;
    node->parent_->is_black_ = true;
    brother->right_->is_black_ = true;
    rotate_left(node->parent_);
    node = root_;
  }
}

template <class Key, class Value>
void BinaryTree<Key, Value>::case_node_right(node_type &node) {
  node_type brother = node->parent_->left_;
  if (!brother->is_black_) {
    change_colors_two(brother, node->parent_);
    rotate_right(node->parent_);
    brother = node->parent_->left_;
  }
  if (brother->left_->is_black_ && brother->right_->is_black_) {
    brother->is_black_ = false;
    node = node->parent_;
  } else {
    if (brother->left_->is_black_) {
      change_colors_two(brother->right_, brother);
      rotate_left(brother);
      brother = node->parent_->left_;
    }
    brother->is_black_ = node->parent_->is_black_;
    node->parent_->is_black_ = true;
    brother->left_->is_black_ = true;
    rotate_right(node->parent_);
    node = root_;
  }
}

template <class Key, class Value>
void BinaryTree<Key, Value>::to_file() {
  if (root_->is_nil()) {
    return;
  }
  std::ofstream fout;
  fout.open("draw.dot", std::ios::trunc);
  fout << "digraph G {\n";
  fout << root_->to_dot_text();
  fout << "}\n";
  fout.close();
}

template <class Key, class Value>
typename BinaryTree<Key, Value>::iterator BinaryTree<Key, Value>::begin()
    const {
  return iterator(root_->get_minimum());
}

template <class Key, class Value>
typename BinaryTree<Key, Value>::iterator BinaryTree<Key, Value>::end() const {
  return iterator(nil_);
}

}  // namespace s21

#endif  // SRC_S21_BINARY_TREE_TPP_
