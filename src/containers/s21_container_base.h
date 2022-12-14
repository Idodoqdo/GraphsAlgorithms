// Copyright <jgerrick, kmodesta, lwolmer, tfelton> 2022
#ifndef SRC_S21_CONTAINER_BASE_H_
#define SRC_S21_CONTAINER_BASE_H_
#include <cstdlib>
#include <utility>
namespace s21 {
template <class ValueType>
class Container {
 public:
  using size_type = size_t;
  virtual ~Container() = default;
  /**
      @brief Checks if container is empty

      @return true if empty, false otherwise
  */
  virtual bool empty() = 0;
  /**
      @brief Calculates number of elements in container

      @return size_t : Number of elements
  */
  virtual size_type size() = 0;
};
}  // namespace s21

#endif  // SRC_S21_CONTAINER_BASE_H_
