// Copyright <jgerrick, kmodesta, lwolmer, tfelton> 2022
#ifndef SRC_S21_ARRAY_H_
#define SRC_S21_ARRAY_H_

#include <cassert>

#include "s21_vector.h"

namespace s21 {
template <typename T, std::size_t N>
class basearray : public vector<T> {
 public:
  using value_type = typename vector<T>::value_type;
  using reference = typename vector<T>::reference;
  using const_reference = typename vector<T>::const_reference;
  using iterator = typename vector<T>::iterator;
  using const_iterator = typename vector<T>::const_iterator;
  using size_type = typename vector<T>::size_type;

  size_type max_size() { return N; }

  void swap(basearray &other) {
    assert(other.size_ == N && "invalid_argument");
    for (size_type i = 0; i < N; ++i) {
      std::swap(data_[i], other.data_[i]);
    }
  }

  void fill(const_reference value) {
    for (size_type i = 0; i < N; ++i) {
      data_[i] = value;
    }
  }

 protected:
  explicit basearray(T *data) : s21::vector<T>(data, N) { data_ = data; }

 private:
  size_type size_ = N;
  T *data_;
  using vector<T>::max_size;
  using vector<T>::reserve;
  using vector<T>::capacity;
  using vector<T>::shrink_to_fit;
  using vector<T>::clear;
  using vector<T>::insert;
  using vector<T>::erase;
  using vector<T>::push_back;
  using vector<T>::pop_back;
  using vector<T>::swap;
  using vector<T>::emplace;
  using vector<T>::emplace_back;
};

template <typename T, size_t N>
class array : public basearray<T, N> {
 public:
  using value_type = typename vector<T>::value_type;
  using reference = typename vector<T>::reference;
  using const_reference = typename vector<T>::const_reference;
  using iterator = typename vector<T>::iterator;
  using const_iterator = typename vector<T>::const_iterator;
  using size_type = typename vector<T>::size_type;
  array() : basearray<T, N>(data_) { memset(data_, 0, N * sizeof(value_type)); }

  array(std::initializer_list<T> const &items) : array() {
    assert(items.size() <= N && "invalid_argument");
    int count = 0;
    for (auto &item : items) {
      data_[count] = item;
      ++count;
    }
  }

  array(const array &a) : array() {
    assert(a.size_ == N && "invalid_argument");
    std::memcpy(data_, a.data_, N * sizeof(value_type));
    size_ = a.size_;
  }

  array(array &&a) : array() {
    assert(a.size_ == N && "invalid_argument");
    std::swap(data_, a.data_);
    size_ = a.size_;
  }

  ~array() = default;

  array<T, N> operator=(array &&a) {
    if (&a != this) {
      assert(N == a.size_ && "invalid_argument");
      std::memcpy(data_, a.data_, N * sizeof(value_type));
      size_ = a.size_;
    }
    return *this;
  }

 private:
  value_type data_[N];
  size_type size_ = N;
};

template <typename T>
class array<T, 0> : public basearray<T, 0> {
 public:
  array() : basearray<T, 0>(nullptr) {}
};

}  // namespace s21

#endif  // SRC_S21_ARRAY_H_
