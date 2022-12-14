// Copyright <jgerrick, kmodesta, lwolmer, tfelton> 2022
#ifndef SRC_S21_SORTED_H_
#define SRC_S21_SORTED_H_
#include <limits>

#include "s21_binary_tree.h"
#include "s21_container_base.h"
namespace s21 {
template <class Key, class Value>
class Sorted : public Container<Key> {
 public:
  using size_type = typename Container<Key>::size_type;
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename BinaryTree<key_type, mapped_type>::iterator;
  using const_iterator =
      typename BinaryTree<key_type, mapped_type>::const_iterator;
  using node_allocator =
      typename std::allocator_traits<std::allocator<key_type>>::
          template rebind_alloc<TreeNode<key_type, key_type>>;

  iterator begin() const { return tree_.begin(); }
  iterator end() const { return tree_.end(); }
  bool empty() override { return !tree_.get_size(); }
  size_type size() override { return tree_.get_size(); }
  size_type max_size() { return allocator_.max_size(); }
  void clear() { tree_.clear_tree(tree_.get_root()); }
  void erase(iterator pos) { tree_.erase_node(pos); }
  virtual void erase(key_type key) {
    auto it_pair = tree_.find(key);
    if (it_pair.second) erase(it_pair.first);
  }
  bool contains(const key_type &key) { return tree_.find(key).second; }

 protected:
  BinaryTree<key_type, mapped_type> tree_ = {};
  node_allocator allocator_ = {};
};
}  // namespace s21

#endif  // SRC_S21_SORTED_H_
