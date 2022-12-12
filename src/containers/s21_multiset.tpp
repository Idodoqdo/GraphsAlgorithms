// Copyright <jgerrick, kmodesta, lwolmer, tfelton> 2022

#ifndef SRC_S21_MULTISET_TPP_
#define SRC_S21_MULTISET_TPP_
#include <limits>
#include <stdexcept>

#include "s21_binary_tree.h"
#include "s21_multiset.h"

namespace s21 {

template <class key_type>
multiset<key_type>::multiset(
    std::initializer_list<multiset<key_type>::value_type> const &items) {
  for (const key_type &val : items) {
    this->insert(val);
  }
}

template <class key_type>
multiset<key_type>::multiset(const multiset<key_type> &other)
    : set<key_type>(other) {
  this->tree_ = other.tree_;
}

template <class key_type>
multiset<key_type>::multiset(const multiset<key_type> &&other) {
  if (this != &other) {
    set<key_type>::tree_ = std::move(other.tree_);
    set<key_type>::allocator_ = std::move(other.allocator_);
  }
}

template <class key_type>
multiset<key_type> &multiset<key_type>::operator=(multiset<key_type> &&other) {
  if (this != &other) {
    set<key_type>::tree_ = std::move(other.tree_);
    set<key_type>::allocator_ = std::move(other.allocator_);
  }
  return *this;
}

template <class key_type>
std::pair<typename multiset<key_type>::iterator, bool>
multiset<key_type>::insert(const value_type &value) {
  std::pair<key_type, std::nullptr_t> p;
  p.first = value;
  auto two_key_it = this->tree_.insert_node(p, true);
  return std::make_pair(iterator(two_key_it.first), two_key_it.second);
}

template <class key_type>
void multiset<key_type>::merge(multiset<key_type> &other) {
  for (auto i : other) {
    this->insert(i);
  }
  other.clear();
}

template <class key_type>
void multiset<key_type>::swap(multiset<key_type> &other) {
  std::swap(this->tree_, other.tree_);
}

template <class key_type>
template <class... Args>
std::pair<typename multiset<key_type>::iterator, bool>
multiset<key_type>::emplace(Args &&...args) {
  std::pair<iterator, bool> return_value = std::make_pair(this->end(), false);
  std::initializer_list<key_type> arg{args...};
  if (arg.size() == 0) {
    auto it_pair =
        this->tree_.insert_node(std::make_pair(key_type(), nullptr), true);
    return_value = std::make_pair(iterator(it_pair.first), it_pair.second);
  } else {
    for (auto &val : arg) {
      auto it_pair =
          this->tree_.insert_node(std::make_pair(val, nullptr), true);
      return_value = std::make_pair(iterator(it_pair.first), it_pair.second);
    }
  }

  return return_value;
}

template <class key_type>
std::pair<typename multiset<key_type>::iterator,
          typename multiset<key_type>::iterator>
multiset<key_type>::equal_range(const key_type &key) {
  return std::make_pair(lower_bound(key), upper_bound(key));
}

template <class key_type>
typename multiset<key_type>::iterator multiset<key_type>::lower_bound(
    const key_type &key) {
  auto return_value = begin();
  while (return_value != this->end() && *return_value < key) ++return_value;
  return iterator(return_value);
}

template <class key_type>
typename multiset<key_type>::iterator multiset<key_type>::upper_bound(
    const key_type &key) {
  auto return_value = lower_bound(key);
  while (return_value != this->end() && *return_value <= key) ++return_value;
  return return_value;
}

template <class key_type>
typename multiset<key_type>::size_type multiset<key_type>::count(
    const key_type &key) {
  auto upper_bound = lower_bound(key);
  size_type count = 0;
  while (*upper_bound == key) {
    ++upper_bound;
    count++;
  }
  return count;
}

template <class key_type>
void multiset<key_type>::erase(key_type key) {
  auto it = lower_bound(key);
  while (it != this->end() && *it == key) {
    this->erase(it);
    it = lower_bound(key);
  }
}
}  // namespace s21

#endif  // SRC_S21_MULTISET_TPP_
