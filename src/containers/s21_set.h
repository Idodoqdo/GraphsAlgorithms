// Copyright <jgerrick, kmodesta, lwolmer, tfelton> 2022
#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_

#include "s21_binary_tree.h"
#include "s21_sorted.h"

namespace s21 {

template <class Key>
class set : private Sorted<Key, std::nullptr_t> {
 public:
  using key_type = Key;
  using mapped_type = std::nullptr_t;
  using value_type = key_type;
  using reference = key_type &;
  using const_reference = const key_type &;
  using iterator = typename BinaryTree<key_type, mapped_type>::one_key_iterator;
  using const_iterator =
      typename BinaryTree<key_type, mapped_type>::const_one_key_iterator;
  using size_type = size_t;

  using Container<Key>::size;
  using Container<Key>::empty;
  using Sorted<Key, std::nullptr_t>::tree_;
  using Sorted<Key, std::nullptr_t>::allocator_;
  using Sorted<Key, std::nullptr_t>::contains;
  using Sorted<Key, std::nullptr_t>::erase;
  using Sorted<Key, std::nullptr_t>::clear;
  using Sorted<Key, std::nullptr_t>::max_size;

  iterator begin() const { return iterator(this->tree_.begin()); }
  iterator end() const { return iterator(this->tree_.end()); }

  set() = default;
  set(std::initializer_list<value_type> const &items);
  set(const set<key_type> &other);
  set(const set<key_type> &&other);
  set<key_type> &operator=(set<key_type> &&other);

  iterator find(const_reference key);
  void merge(set<key_type> &other);
  void swap(set<key_type> &other);

  virtual std::pair<iterator, bool> insert(const value_type &value);

  template <typename... Args>
  std::pair<iterator, bool> emplace(Args &&...args);
};
}  // namespace s21
#include "s21_set.tpp"
#endif  // SRC_S21_SET_H_
