// Copyright <jgerrick, kmodesta, lwolmer, tfelton> 2022
#ifndef SRC_S21_STACK_TPP_
#define SRC_S21_STACK_TPP_
#include "s21_stack.h"
namespace s21 {
template <class T>
stack<T>::stack() {
  create();
}

template <class T>
stack<T>::stack(const stack &other) {
  if (this != &other) {
    create();
    for (size_type j = other.cur_size_; other.cur_size_ != cur_size_; --j) {
      node *tmp = other.head_;
      for (size_type i = j; i > 0; --i) tmp = tmp->next;
      push(tmp->value_);
    }
  }
}

template <class T>
stack<T>::stack(stack &&other) {
  if (this != &other) {
    create();
    swap(other);
  }
}

template <class T>
stack<T> &stack<T>::operator=(stack &&other) {
  if (this != &other) swap(other);
  return *this;
}

template <class T>
typename stack<T>::size_type stack<T>::size() {
  return cur_size_;
}

template <class T>
stack<T>::~stack() {
  this->clear();
  delete head_;
}

template <class T>
void stack<T>::clear() {
  while (cur_size_) pop();
}

template <class T>
typename stack<T>::const_reference stack<T>::top() {
  return head_->next->value_;
}

template <class T>
bool stack<T>::empty() {
  return cur_size_ == 0;
}

template <class T>
stack<T>::stack(std::initializer_list<value_type> const &items) {
  create();
  for (auto &i : items) push(i);
}

template <class T>
void stack<T>::push(const_reference value) {
  node *tmp = new node(value);
  if (tmp == nullptr) throw std::bad_alloc();
  tmp->next = head_->next;
  head_->next = tmp;
  ++cur_size_;
}

template <class T>
void stack<T>::pop() {
  node *tmp;
  if (empty()) throw std::invalid_argument("the list is empty");
  tmp = head_->next;
  head_->next = head_->next->next;
  delete tmp;
  --cur_size_;
}

template <class T>
void stack<T>::swap(stack &other) {
  std::swap(head_, other.head_);
  std::swap(cur_size_, other.cur_size_);
}

template <class T>
void stack<T>::create() {
  head_ = new node();
  head_->next = nullptr;
  cur_size_ = 0;
}

template <class T>
template <class... Args>
void stack<T>::emplace_front(Args &&...args) {
  if ((sizeof...(args)) == 0) {
    value_type _empty = {};
    push(_empty);
  }
  std::initializer_list<T> arg{args...};
  for (auto &val : arg) push(val);
}
}  // namespace s21
#endif  // SRC_S21_STACK_TPP_
