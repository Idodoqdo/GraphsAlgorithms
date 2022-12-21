// Copyright <jgerrick, kmodesta, lwolmer, tfelton> 2022
#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

#include <stdexcept>

#include "s21_container_base.h"
namespace s21 {
template <class T>
class stack : public Container<T> {
  struct node {
    T value_;
    node *next;
    node() : value_(), next(nullptr) {}
    explicit node(T val) : value_(val), next(nullptr) {}
  };

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = typename Container<T>::size_type;

 public:
  stack();
  stack(const stack &other);
  stack(stack &&other);
  stack &operator=(stack &&other);
  size_type size() override;
  ~stack();
  void clear();
  const_reference top();
  bool empty() override;
  explicit stack(std::initializer_list<value_type> const &items);
  void push(const_reference value);
  void pop();
  void swap(stack &other);

  template <class... Args>
  void emplace_front(Args &&... args);

 private:
  size_type cur_size_;
  node *head_;
  void create();
};
}  // namespace s21
#include "s21_stack.tpp"
#endif  // SRC_S21_STACK_H_
