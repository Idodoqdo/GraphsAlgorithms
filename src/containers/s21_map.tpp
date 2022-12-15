// Copyright <jgerrick, kmodesta, lwolmer, tfelton> 2022

#ifndef SRC_S21_MAP_TPP_
#define SRC_S21_MAP_TPP_
#include <limits>
#include <stdexcept>

namespace s21 {

template <class key_type, class mapped_type>
map<key_type, mapped_type>::map(
    std::initializer_list<value_type> const &items) {
  for (const_reference val : items) {
    insert(val);
  }
}

template <class key_type, class mapped_type>
map<key_type, mapped_type>::map(const map<key_type, mapped_type> &other) {
  Sorted<key_type, mapped_type>::tree_ = other.tree_;
}

template <class key_type, class mapped_type>
map<key_type, mapped_type>::map(map &&other) {
  if (this != &other) {
    Sorted<key_type, mapped_type>::tree_ = std::move(other.tree_);
    Sorted<key_type, mapped_type>::allocator_ = std::move(other.allocator_);
  }
}

template <class key_type, class mapped_type>
typename map<key_type, mapped_type>::mapped_type &
map<key_type, mapped_type>::at(const key_type &key) {
  std::pair<iterator, bool> it_pair = this->tree_.find(key);
  if (!it_pair.second)
    throw std::out_of_range("Map doesn't contains a value with given key");
  iterator i = it_pair.first;
  return (*i).second;
}

template <class key_type, class mapped_type>
typename map<key_type, mapped_type>::mapped_type &
map<key_type, mapped_type>::operator[](const key_type &key) {
  std::pair<iterator, bool> it_pair = this->tree_.find(key);
  if (!it_pair.second) {
    it_pair = insert(key, mapped_type());
  }
  iterator i = it_pair.first;
  return (*i).second;
}

template <class key_type, class mapped_type>
void map<key_type, mapped_type>::merge(map<key_type, mapped_type> &other) {
  for (auto i = other.begin(); i != other.end(); ++i) {
    insert(*i);
  }
  other.clear();
}

template <class key_type, class mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert(const_reference value) {
  auto has_it = this->tree_.find(value.first);
  if (has_it.second) {
    has_it.second = false;
    return has_it;
  } else {
    return this->tree_.insert_node(value, false);
  }
}

template <class key_type, class mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert(const key_type &key,
                                   const mapped_type &obj) {
  return insert(std::pair<key_type, mapped_type>(key, obj));
}

template <class key_type, class mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert_or_assign(
    const map<key_type, mapped_type>::key_type &key,
    const map<key_type, mapped_type>::mapped_type &obj) {
  std::pair<iterator, bool> it_pair = this->tree_.find(key);
  if (it_pair.second) {
    this->erase(it_pair.first);
  }
  it_pair = insert(std::make_pair(key, obj));
  return it_pair;
}

template <class key_type, class mapped_type>
map<key_type, mapped_type> &map<key_type, mapped_type>::operator=(
    map<key_type, mapped_type> &&other) {
  if (this != &other) {
    Sorted<key_type, mapped_type>::tree_ = std::move(other.tree_);
    Sorted<key_type, mapped_type>::allocator_ = std::move(other.allocator_);
  }
  return *this;
}

template <class key_type, class mapped_type>
void map<key_type, mapped_type>::swap(map<key_type, mapped_type> &other) {
  std::swap(this->tree_, other.tree_);
}

template <class key_type, class mapped_type>
template <class... Args>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::emplace(Args &&...args) {
  std::pair<iterator, bool> return_value = std::make_pair(this->end(), false);
  std::initializer_list<value_type> arg{args...};
  if (arg.size() == 0) {
    return_value = this->tree_.insert_node(
        std::make_pair(key_type(), mapped_type()), false);
  } else {
    for (auto &val : arg) {
      return_value = this->tree_.insert_node(val, false);
    }
  }
  return return_value;
}
}  // namespace s21

#endif  // SRC_S21_MAP_TPP_
