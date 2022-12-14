// Copyright <jgerrick, kmodesta, lwolmer, tfelton> 2022
#ifndef SRC_S21_MULTISET_H_
#define SRC_S21_MULTISET_H_

#include "s21_binary_tree.h"
#include "s21_set.h"

namespace s21 {

template <class Key>
class multiset : private set<Key> {
 public:
  using key_type = Key;
  using mapped_type = std::nullptr_t;
  using value_type = key_type;
  using reference = key_type &;
  using const_reference = const key_type &;
  using iterator = typename BinaryTree<key_type, mapped_type>::one_key_iterator;
  using const_iterator =
      typename BinaryTree<key_type, mapped_type>::const_one_key_iterator;
  using size_type = typename Container<Key>::size_type;

  using Container<Key>::size;
  using Container<Key>::empty;
  using Sorted<Key, std::nullptr_t>::contains;
  using Sorted<Key, std::nullptr_t>::erase;
  using Sorted<Key, std::nullptr_t>::clear;
  using Sorted<Key, std::nullptr_t>::max_size;
  using set<Key>::begin;
  using set<Key>::end;
  using set<Key>::find;
  using set<Key>::insert;
  using set<Key>::emplace;
  using set<Key>::tree_;
  using set<Key>::allocator_;

  multiset() = default;
  multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset<key_type> &other);
  multiset(const multiset<key_type> &&other);
  multiset<key_type> &operator=(multiset<key_type> &&other);

  void erase(key_type key) override;

  std::pair<iterator, bool> insert(const value_type &value) override;
  void merge(multiset<key_type> &other);
  void swap(multiset<key_type> &other);

  template <typename... Args>
  std::pair<iterator, bool> emplace(Args &&...args);

  std::pair<iterator, iterator> equal_range(const key_type &key);
  iterator lower_bound(const key_type &key);
  iterator upper_bound(const key_type &key);
  size_type count(const key_type &key);
};
}  // namespace s21
#include "s21_multiset.tpp"
#endif  // SRC_S21_MULTISET_H_
