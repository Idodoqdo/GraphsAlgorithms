// Copyright <jgerrick, kmodesta, lwolmer, tfelton> 2022
#ifndef SRC_S21_QUEUE_H_
#define SRC_S21_QUEUE_H_

#include <stdexcept>

#include "s21_container_base.h"
namespace s21 {
template <class T>
class queue : public Container<T> {
  struct node {
    T value_;
    node *next;
    node() : value_(), next(nullptr) {}
    explicit node(const T &val) : value_(val), next(nullptr) {}
  };

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = typename Container<T>::size_type;

 public:
  queue();
  queue(const queue &other);
  queue(queue &&other);
  queue &operator=(queue &&other);
  size_type size() override;
  ~queue();
  void clear();
  const_reference front();
  const_reference back();
  bool empty() override;
  explicit queue(std::initializer_list<value_type> const &items);
  void pop();
  void push(const_reference value);
  void swap(queue &other);

  template <class... Args>
  void emplace_back(Args &&...args);

 private:
  size_type cur_size_;
  node *head_;
  node *tail_;

  void create();
};
}  // namespace s21
#include "s21_queue.tpp"
#endif  // SRC_S21_QUEUE_H_
