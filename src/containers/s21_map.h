// Copyright <jgerrick, kmodesta, lwolmer, tfelton> 2022
#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_
#include <algorithm>

#include "s21_binary_tree.h"
#include "s21_sorted.h"
namespace s21 {
template <class Key, class Value>
class map : public Sorted<Key, Value> {
 public:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename BinaryTree<key_type, mapped_type>::iterator;
  using const_iterator =
      typename BinaryTree<key_type, mapped_type>::const_iterator;
  using size_type = typename Container<key_type>::size_type;

  map() = default;
  map(std::initializer_list<value_type> const& items);
  map(const map& other);
  map(map&& other);

  mapped_type& at(const key_type& key);
  mapped_type& operator[](const key_type& key);

  void merge(map<key_type, mapped_type>& other);
  void swap(map<key_type, mapped_type>& other);

  std::pair<iterator, bool> insert(const_reference value);
  std::pair<iterator, bool> insert(const key_type& key, const mapped_type& obj);
  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj);

  map<key_type, mapped_type>& operator=(map<key_type, mapped_type>&& other);

  template <typename... Args>
  std::pair<iterator, bool> emplace(Args&&... args);
};

}  // namespace s21
#include "s21_map.tpp"

#endif  // SRC_S21_MAP_H_
