// Copyright <jgerrick, kmodesta, lwolmer, tfelton> 2022
#ifndef SRC_S21_LIST_TPP_
#define SRC_S21_LIST_TPP_
#include "s21_list.h"
namespace s21 {
template <class T>
void list<T>::create() {
  cicle_ = new node();
  cicle_->next = cicle_;
  cicle_->prev = cicle_;
  cur_size_ = 0;
}

template <class T>
bool list<T>::exists(const node *N) {
  return N != cicle_;
}

template <class T>
bool list<T>::is_cicle(const node *N) {
  return N == cicle_;
}

template <class T>
typename list<T>::iterator list<T>::insert_ptr(
    typename list<T>::iterator pos1, typename list<T>::iterator pos2) {
  node *elm1 = pos1.target_;
  node *elm2 = pos2.target_;
  elm2->prev->next = elm2->next;
  elm2->next->prev = elm2->prev;
  elm2->next = elm1;
  elm2->prev = elm1->prev;
  elm1->prev->next = elm2;
  elm1->prev = elm2;
  return List_Iterator(elm1);
}

template <class T>
typename list<T>::iterator list<T>::begin() {
  return iterator(cicle_->next);
}

template <class T>
typename list<T>::const_iterator list<T>::begin() const {
  return iterator(cicle_->next);
}

template <class T>
typename list<T>::iterator list<T>::end() {
  return iterator(cicle_);
}

template <class T>
typename list<T>::const_iterator list<T>::end() const {
  return list<T>::iterator(cicle_);
}

template <class T>
list<T>::list() {
  create();
}

template <class T>
list<T>::list(size_type n) {
  create();
  for (; n > 0; --n) push_back(cicle_->value_);
}

template <class T>
list<T>::list(const list &other) {
  if (this != &other) {
    create();
    node *tmp = other.cicle_->next;
    for (size_type i = 0; i < other.cur_size_; ++i) {
      push_back(tmp->value_);
      tmp = tmp->next;
    }
  }
}

template <class T>
list<T>::list(list &&other) {
  if (this != &other) {
    create();
    swap(other);
  }
}

template <class T>
list<T> &list<T>::operator=(const list &other) {
  if (this != &other) {
    create();
    node *tmp = other.cicle_->next;
    for (size_type i = 0; i < other.cur_size_; ++i) {
      push_back(tmp->value_);
      tmp = tmp->next;
    }
  }
  return *this;
}

template <class T>
list<T> &list<T>::operator=(list &&other) {
  if (this != &other) swap(other);
  return *this;
}

template <class T>
typename list<T>::size_type list<T>::size() {
  return cur_size_;
}

template <class T>
list<T>::~list() {
  this->clear();
  delete cicle_;
}

template <class T>
void list<T>::clear() {
  while (cur_size_) pop_back();
}

template <class T>
typename list<T>::const_reference list<T>::front() {
  return cicle_->next->value_;
}

template <class T>
typename list<T>::const_reference list<T>::back() {
  return cicle_->prev->value_;
}

template <class T>
bool list<T>::empty() {
  return is_cicle(cicle_->next);
}

template <class T>
list<T>::list(std::initializer_list<value_type> const &items) {
  create();
  for (auto &i : items) push_back(i);
}

template <class T>
void list<T>::push_front(const_reference value) {
  node *tmp = new node(value);
  if (tmp == NULL) throw std::bad_alloc();
  tmp->next = cicle_->next;
  tmp->prev = cicle_;
  cicle_->next->prev = tmp;
  cicle_->next = tmp;
  ++cur_size_;
}

template <class T>
void list<T>::pop_front() {
  node *tmp;
  if (empty()) throw std::invalid_argument("the list is empty");
  tmp = cicle_->next;
  cicle_->next = cicle_->next->next;
  cicle_->next->prev = cicle_;
  delete tmp;
  --cur_size_;
}

template <class T>
void list<T>::push_back(const_reference value) {
  node *tmp = new node(value);
  if (tmp == NULL) throw std::bad_alloc();
  tmp->next = cicle_;
  tmp->prev = cicle_->prev;
  cicle_->prev->next = tmp;
  cicle_->prev = tmp;
  ++cur_size_;
}

template <class T>
void list<T>::pop_back() {
  node *tmp;
  if (empty()) throw std::invalid_argument("the list is empty");
  tmp = cicle_->prev;
  cicle_->prev = cicle_->prev->prev;
  cicle_->prev->next = cicle_;
  delete tmp;
  --cur_size_;
}

template <class T>
typename list<T>::iterator list<T>::insert(
    typename list<T>::iterator pos, typename list<T>::const_reference value) {
  node *elm = pos.target_;
  node *ins = new node(value);
  ins->next = elm;
  ins->prev = elm->prev;
  elm->prev->next = ins;
  elm->prev = ins;
  ++cur_size_;
  return List_Iterator(ins);
}

template <class T>
void list<T>::erase(iterator pos) {
  if (exists(pos.target_)) {
    node *elm = pos.target_;
    elm->prev->next = elm->next;
    elm->next->prev = elm->prev;
    delete elm;
    --cur_size_;
  }
}

template <class T>
void list<T>::swap(list &other) {
  std::swap(cicle_, other.cicle_);
  std::swap(cur_size_, other.cur_size_);
}

template <class T>
void list<T>::merge(list &other) {
  iterator iter1 = begin(), iter2 = other.begin();
  while (iter2 != other.end()) {
    if (*iter1 < *iter2) {
      if (iter1 != end()) ++iter1;
    } else {
      insert_ptr(iter1, iter2);
      ++cur_size_;
      --other.cur_size_;
      iter2 = other.begin();
    }
  }
}

template <class T>
void list<T>::splice(const_iterator pos, list &other) {
  iterator iter2 = other.begin();
  while (iter2 != other.end()) {
    insert_ptr(pos, iter2);
    ++cur_size_;
    iter2 = other.begin();
  }
  other.cur_size_ = 0;
}

template <class T>
void list<T>::reverse() {
  for (iterator iter1 = iterator(cicle_->next->next); iter1 != end();) {
    iterator iter_tmp = iter1;
    ++iter1;
    insert_ptr(begin(), iter_tmp);
  }
}

template <class T>
typename list<T>::size_type list<T>::max_size() {
  return node_allocator().max_size();
}

template <class T>
void list<T>::unique() {
  for (iterator iter2 = begin(); iter2.target_ != cicle_->prev; ++iter2) {
    iterator iter3 = iter2;
    ++iter3;
    if (*iter2 == *iter3) erase(iter3);
  }
}

template <class T>
void list<T>::sort() {
  for (size_type i = 0; i < cur_size_; ++i) {
    for (iterator iter1 = begin(); iter1.target_ != cicle_->prev; ++iter1) {
      iterator iter2 = iter1;
      ++iter2;
      if (*iter1 > *iter2) insert_ptr(iter1, iter2);
    }
  }
}

template <class T>
template <class... Args>
void list<T>::emplace_front(Args &&... args) {
  if ((sizeof...(args)) == 0) {
    value_type _empty = {};
    push_front(_empty);
  }
  std::initializer_list<T> arg{args...};
  for (auto &val : arg) push_front(val);
}

template <class T>
template <class... Args>
void list<T>::emplace_back(Args &&... args) {
  if ((sizeof...(args)) == 0) {
    value_type _empty = {};
    push_back(_empty);
  }
  std::initializer_list<T> arg{args...};
  for (auto &val : arg) push_back(val);
}

template <class T>
template <class... Args>
typename list<T>::iterator list<T>::emplace(const_iterator pos,
                                            Args &&... args) {
  if ((sizeof...(args)) == 0) {
    value_type _empty = {};
    insert(pos, _empty);
  }
  std::initializer_list<T> arg{args...};
  for (auto &val : arg) insert(pos, val);
  return pos;
}
}  // namespace s21
#endif  // SRC_S21_LIST_TPP_
