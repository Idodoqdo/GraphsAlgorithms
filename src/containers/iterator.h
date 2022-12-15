#ifndef SRC_ITERATOR_H_
#define SRC_ITERATOR_H_

namespace s21 {
template <typename T>
class iterator {
 public:
  T& operator*() { return *pointer_; }

  void operator++() { ++pointer_; }

  void operator--() { --pointer_; }

  bool operator==(const iterator& other) const {
    return pointer_ == other.pointer_;
  }

  bool operator!=(const iterator& other) const {
    return pointer_ != other.pointer_;
  }

 protected:
  explicit iterator(T* pointer) : pointer_(pointer) {}

 private:
  T* pointer_;
};
}  // namespace s21

#endif  // SRC_ITERATOR_H_
