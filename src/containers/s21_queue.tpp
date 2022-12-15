// Copyright <jgerrick, kmodesta, lwolmer, tfelton> 2022
#ifndef SRC_S21_QUEUE_TPP_
#define SRC_S21_QUEUE_TPP_
#include "s21_queue.h"
namespace s21 {
template <class T>
queue<T>::queue() {
  create();
}

template <class T>
queue<T>::queue(const queue &other) {
  if (this != &other) {
    create();
    node *tmp = other.head_->next;
    while (cur_size_ < other.cur_size_) {
      push(tmp->value_);
      tmp = tmp->next;
    }
  }
}

template <class T>
queue<T>::queue(queue &&other) {
  if (this != &other) {
    create();
    swap(other);
  }
}

template <class T>
queue<T> &queue<T>::operator=(queue &&other) {
  if (this != &other) swap(other);
  return *this;
}

template <class T>
typename queue<T>::size_type queue<T>::size() {
  return cur_size_;
}

template <class T>
queue<T>::~queue() {
  this->clear();
  delete head_;
}

template <class T>
void queue<T>::clear() {
  while (cur_size_) pop();
}

template <class T>
typename queue<T>::const_reference queue<T>::front() {
  return head_->next->value_;
}

template <class T>
typename queue<T>::const_reference queue<T>::back() {
  return tail_->value_;
}

template <class T>
bool queue<T>::empty() {
  return cur_size_ == 0;
}

template <class T>
queue<T>::queue(std::initializer_list<value_type> const &items) {
  create();
  for (auto &i : items) push(i);
}

template <class T>
void queue<T>::pop() {
  node *tmp;
  if (empty()) throw std::invalid_argument("the queue is empty");
  tmp = head_->next;
  head_->next = head_->next->next;
  delete tmp;
  --cur_size_;
  if (empty())
  create();
}

template <class T>
void queue<T>::push(const_reference value) {
  node *tmp = new node(value);
  if (tmp == NULL) throw std::bad_alloc();
  tail_->next = tmp;
  tail_ = tmp;
  tmp->next = nullptr;
  ++cur_size_;
}

template <class T>
void queue<T>::swap(queue &other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(cur_size_, other.cur_size_);
}

template <class T>
void queue<T>::create() {
  head_ = new node();
  head_->next = tail_;
  tail_ = head_;
  cur_size_ = 0;
}

template <class T>
template <class... Args>
void queue<T>::emplace_back(Args &&...args) {
  if ((sizeof...(args)) == 0) {
    value_type _empty = {};
    push(_empty);
  }
  std::initializer_list<T> arg{args...};
  for (auto &val : arg) push(val);
}
}  // namespace s21
#endif  // SRC_S21_QUEUE_TPP_
