// Copyright <jgerrick, kmodesta, lwolmer, tfelton> 2022
#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include <iostream>

#include "s21_container_base.h"

namespace s21 {
template <class T>
class list : public Container<T> {
 public:
  struct node {
    T value_;
    node* next;
    node* prev;
    node() : value_(), next(nullptr), prev(nullptr) {}
    explicit node(const T& val) : value_(val), next(nullptr), prev(nullptr) {}
  };
  class List_Iterator {
   public:
    node* target_;
    using difference_type = long;
    using value_type = long;
    using pointer = const long*;
    using reference = const long&;
    using iterator_category = std::forward_iterator_tag; 

    List_Iterator() : target_(nullptr) {}
    explicit List_Iterator(node* target_) : target_(target_) {}

    T& operator*() const { return target_->value_; }

    List_Iterator& operator++() {
      target_ = target_->next;
      return *this;
    }

    List_Iterator operator++(int) {
      target_ = target_->next;
      return *this;
    }

    List_Iterator& operator--() {
      target_ = target_->prev;
      return *this;
    }

    List_Iterator operator--(int) {
      target_ = target_->prev;
      return *this;
    }

    bool operator==(List_Iterator const& r) { return (target_ == r.target_); }

    bool operator!=(List_Iterator const& r) { return (target_ != r.target_); }
  };
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = List_Iterator;
  using const_iterator = const List_Iterator;
  using size_type = typename Container<T>::size_type;
  using node_allocator = typename std::allocator_traits<
      std::allocator<T>>::template rebind_alloc<node>;

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;
  list();
  explicit list(size_type n);
  list(const list& other);
  list(list&& other);
  list& operator=(const list& other);
  list& operator=(list&& other);
  size_type size() override;
  ~list();
  void clear();
  const_reference front();
  const_reference back();
  bool empty() override;
  list(std::initializer_list<value_type> const& items);
  void push_front(const_reference value);
  void pop_front();
  void push_back(const_reference value);
  void pop_back();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void swap(list& other);
  void merge(list& other);
  void splice(const_iterator pos, list& other);
  void reverse();
  void unique();
  void sort();
  size_type max_size();

  template <class... Args>
  void emplace_front(Args&&... args);
  template <class... Args>
  void emplace_back(Args&&... args);
  template <class... Args>
  iterator emplace(const_iterator pos, Args&&... args);

 private:
  size_type cur_size_;
  node* cicle_;

  void create();
  bool exists(const node* N);
  bool is_cicle(const node* N);
  iterator insert_ptr(iterator pos1, iterator pos2);
};

}  // namespace s21
#include "s21_list.tpp"
#endif  // SRC_S21_LIST_H_
