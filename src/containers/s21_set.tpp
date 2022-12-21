// Copyright <jgerrick, kmodesta, lwolmer, tfelton> 2022

#ifndef SRC_S21_SET_TPP_
#define SRC_S21_SET_TPP_
#include <limits>
#include <stdexcept>

#include "s21_binary_tree.h"
#include "s21_set.h"
#include "s21_vector.h"

namespace s21 {

template <class key_type>
set<key_type>::set(
    std::initializer_list<set<key_type>::value_type> const &items) {
  for (const_reference val : items) {
    this->insert(val);
  }
}

template <class key_type>
set<key_type>::set(const set<key_type> &other) {
  Sorted<key_type, mapped_type>::tree_ = other.tree_;
  Sorted<key_type, mapped_type>::allocator_ = other.allocator_;
}

template <class key_type>
set<key_type>::set(const set<key_type> &&other) {
  if (this != &other) {
    Sorted<key_type, mapped_type>::tree_ = std::move(other.tree_);
    Sorted<key_type, mapped_type>::allocator_ = std::move(other.allocator_);
  }
}

template <class key_type>
set<key_type> &set<key_type>::operator=(set<key_type> &&other) {
  if (this != &other) {
    Sorted<key_type, mapped_type>::tree_ = std::move(other.tree_);
    Sorted<key_type, mapped_type>::allocator_ = std::move(other.allocator_);
  }
  return *this;
}

template <class key_type>
std::pair<typename set<key_type>::iterator, bool> set<key_type>::insert(
    const_reference value) {
  auto has_it = this->tree_.find(value);
  if (has_it.second) {
    return std::make_pair(iterator(has_it.first), false);
  } else {
    std::pair<key_type, std::nullptr_t> p;
    p.first = value;
    auto insert_it = this->tree_.insert_node(p, false);
    return std::make_pair(iterator(insert_it.first), insert_it.second);
  }
}

template <class key_type>
typename set<key_type>::iterator set<key_type>::find(const_reference &key) {
  return iterator(this->tree_.find(key).first);
}

template <class key_type>
void set<key_type>::merge(set<key_type> &other) {
  for (auto i : other) {
    this->insert(i);
  }
  other.clear();
}

template <class key_type>
template <class... Args>
std::pair<typename set<key_type>::iterator, bool> set<key_type>::emplace(
    Args &&... args) {
  std::pair<iterator, bool> return_value = std::make_pair(this->end(), false);
  std::initializer_list<key_type> arg{args...};
  if (arg.size() == 0) {
    auto it_pair =
        this->tree_.insert_node(std::make_pair(key_type(), nullptr), false);
    return_value = std::make_pair(iterator(it_pair.first), it_pair.second);
  } else {
    for (auto &val : arg) {
      auto it_pair =
          this->tree_.insert_node(std::make_pair(val, nullptr), false);
      return_value = std::make_pair(iterator(it_pair.first), it_pair.second);
    }
  }
  return return_value;
}

template <class key_type>
void set<key_type>::swap(set<key_type> &other) {
  std::swap(this->tree_, other.tree_);
}

}  // namespace s21

#endif  // SRC_S21_SET_TPP_
