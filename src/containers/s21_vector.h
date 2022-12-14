// Copyright <jgerrick, kmodesta, lwolmer, tfelton> 2022
#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_

#include <cmath>
#include <cstring>
#include <stdexcept>

#include "iterator.h"
#include "s21_container_base.h"

namespace s21 {
template <typename T>
class vector : public Container<T> {
 public:
  class VectorIterator : public s21::iterator<T> {
   public:
    explicit VectorIterator(T* pointer) : s21::iterator<T>(pointer) {}
  };

  class VectorConstIterator : public s21::iterator<const T> {
   public:
    explicit VectorConstIterator(T* pointer)
        : s21::iterator<const T>(pointer) {}
  };
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = VectorIterator;
  using const_iterator = VectorConstIterator;
  using size_type = size_t;

  vector();
  explicit vector(size_type n);
  vector(std::initializer_list<value_type> const& items);
  vector(const vector& v);
  vector(vector&& v);
  ~vector();
  vector& operator=(vector&& v);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  T* data();

  iterator begin();
  iterator end();
  const_iterator cbegin();
  const_iterator cend();

  bool empty() override;
  size_type size() override;
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other);

  template <typename... Args>
  iterator emplace(const_iterator pos, Args&&... args);
  template <typename... Args>
  void emplace_back(Args&&... args);

 protected:
  vector(T* data, size_type n) : capacity_(0), size_(n), data_(data) {}

 private:
  size_type capacity_ = 0;
  size_type size_ = 0;
  T* data_ = nullptr;

  void change(size_type size);
  void increase_memory();
};
}  // namespace s21

#include "s21_vector.tpp"

#endif  // SRC_S21_VECTOR_H_
