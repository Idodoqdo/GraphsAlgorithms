// Copyright <jgerrick, kmodesta, lwolmer, tfelton> 2022
#ifndef SRC_S21_BINARY_TREE_H_
#define SRC_S21_BINARY_TREE_H_
#include <cstddef>
#include <fstream>
#include <utility>

#include "s21_tree_node.h"

namespace s21 {

template <class Key>
class set_iterator;

template <class Key, class Value>
class BinaryTree {
 public:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<Key, Value>;
  using size_type = size_t;
  using node_type = TreeNode<Key, Value> *;

  BinaryTree();
  BinaryTree(const BinaryTree &other);
  BinaryTree(BinaryTree &&other);
  ~BinaryTree();
  BinaryTree &operator=(const BinaryTree &other);
  BinaryTree &operator=(BinaryTree &&other);

  class iterator {
    friend BinaryTree;

   public:
    iterator();
    explicit iterator(node_type node);
    iterator(const iterator &other);
    iterator(iterator &&other);
    iterator &operator=(const iterator &other);
    iterator &operator=(iterator &&other);
    iterator &operator++();
    iterator &operator--();
    bool operator==(const iterator &other) const {
      return node_ == other.node_;
    }
    bool operator!=(const iterator &other) const {
      return node_ != other.node_;
    }
    value_type &operator*() { return node_->value_; }

   private:
    node_type node_;
  };

  class const_iterator : public iterator {
    friend BinaryTree;

   public:
    const_iterator() = default;
    explicit const_iterator(iterator it) { this->node_ = it.node_; }
    value_type const &operator*() const { return this->node_->value_; }
  };

  class one_key_iterator : public iterator {
   public:
    one_key_iterator() = default;
    explicit one_key_iterator(iterator it) { this->node_ = it.node_; }
    Key &operator*() { return this->node_->value_.first; }
  };

  class const_one_key_iterator : public one_key_iterator {
    friend BinaryTree;

   public:
    const_one_key_iterator() = default;
    explicit const_one_key_iterator(one_key_iterator it) {
      this->node_ = it.node_;
    }
    Key const &operator*() const { return this->node_->value_.first; }
  };

  // first part of pair is for find() method, second - for contains() method
  std::pair<iterator, bool> find(const key_type &key);
  // is_repeatable = true for multiset
  std::pair<iterator, bool> insert_node(const value_type &value,
                                        bool is_repeatable);
  void erase_node(iterator pos);
  void clear_tree(node_type node);  // can be used for clear() method
  iterator begin() const;
  iterator end() const;
  size_type get_size() const { return size_; }
  node_type get_root() const { return root_; }
  void to_file();

 private:
  size_type size_ = {0};
  node_type root_ = nullptr;
  node_type nil_ = nullptr;
  void naive_insert(node_type node);
  void balance_tree_after_insertion(node_type node);
  void case_parent_left(node_type &node);
  void case_parent_right(node_type &node);
  void change_colors_one(node_type child, node_type uncle);
  void change_colors_two(node_type child, node_type uncle);
  void rotate_right(node_type node);
  void rotate_left(node_type node);
  void connect_to_parent(node_type one, node_type two);
  void balance_tree_after_erasure(node_type node);
  void case_node_left(node_type &node);
  void case_node_right(node_type &node);
};
}  // namespace s21
#include "s21_binary_tree.tpp"
#endif  // SRC_S21_BINARY_TREE_H_
