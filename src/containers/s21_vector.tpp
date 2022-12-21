namespace s21 {
template <typename T>
vector<T>::vector() : vector(0) {}

template <typename T>
vector<T>::vector(size_type n) : capacity_(n), size_(n) {
  if (n > 0) {
    data_ = new value_type[n]();
  }
}

template <typename T>
vector<T>::vector(std::initializer_list<T> const &items)
    : vector(items.size()) {
  int count = 0;
  for (auto &item : items) {
    data_[count] = item;
    ++count;
  }
}

template <typename T>
vector<T>::vector(const vector &v) : capacity_(v.capacity_), size_(v.size_) {
  if (capacity_ > 0) data_ = new value_type[capacity_]();
  std::memcpy(data_, v.data_, v.capacity_ * sizeof(value_type));
}

template <typename T>
vector<T>::vector(vector &&v)
    : capacity_(v.capacity_), size_(v.size_), data_(v.data_) {
  v.size_ = v.capacity_ = 0;
  if (data_ != nullptr) {
    v.data_ = nullptr;
  }
}

template <typename T>
vector<T>::~vector() {
  if (data_ != nullptr && capacity_ != 0) delete[] data_;
}

template <typename T>
vector<T> &vector<T>::operator=(vector &&v) {
  if (&v != this) {
    if (data_ != nullptr) delete[] data_;
    size_ = v.size_;
    capacity_ = v.capacity_;
    data_ = v.data_;
    v.data_ = nullptr;
  }
  return *this;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Value out of range");
  }
  return data_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() {
  return data_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() {
  return data_[size_ - 1];
}

template <typename T>
T *vector<T>::data() {
  return data_;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return iterator(data_);
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return iterator(data_ + size_);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cbegin() {
  return const_iterator(data_);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cend() {
  return const_iterator(data_ + size_);
}

template <typename T>
bool vector<T>::empty() {
  return size_ == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() {
  char bits = 63;
  if (sizeof(void *) == 4) bits = 31;
  return static_cast<size_type>(pow(2, bits)) / sizeof(value_type) - 1;
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size > capacity_) {
    change(size);
    capacity_ = size;
  }
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() {
  return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    change(size_);
    capacity_ = size_;
  }
}

template <typename T>
void vector<T>::change(typename vector<T>::size_type size) {
  T *tmp = new value_type[size];
  for (size_type i = 0; i < size_; ++i) {
    tmp[i] = data_[i];
  }
  if (data_ != nullptr) delete[] data_;
  data_ = tmp;
}

template <typename T>
void vector<T>::clear() {
  size_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  iterator first = begin();
  increase_memory();
  iterator current = begin();
  while (pos != first) {
    --pos;
    ++current;
  }
  iterator result = current;
  value_type tmp = value;
  ++size_;
  std::swap(tmp, *current);
  while (current != end()) {
    ++current;
    std::swap(tmp, *current);
  }
  return result;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  iterator tmp = pos;
  ++tmp;
  while (tmp != end()) {
    *pos = *tmp;
    ++pos;
    ++tmp;
  }
  --size_;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  increase_memory();
  data_[size_] = value;
  ++size_;
}

template <typename T>
void vector<T>::increase_memory() {
  if (size_ == capacity_) {
    if (capacity_ == max_size()) {
      throw std::out_of_range("memory is over");
    } else if (capacity_ * 2 > max_size()) {
      capacity_ = max_size();
    } else {
      capacity_ = capacity_ * 2;
    }
    change(capacity_);
  }
}

template <typename T>
void vector<T>::pop_back() {
  --size_;
}

template <typename T>
void vector<T>::swap(vector &other) {
  std::swap(data_, other.data_);
  std::swap(other.size_, size_);
  std::swap(other.capacity_, capacity_);
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::emplace(const_iterator pos,
                                                Args &&... args) {
  const_iterator first = cbegin();
  size_type size = size_ + sizeof...(args);
  reserve(size);
  size_ = size;
  iterator current = begin();
  while (pos != first) {
    --pos;
    ++current;
  }
  iterator result = current;
  for (size_type i = 0; i < sizeof...(args); ++i) {
    iterator last = end();
    --last;
    iterator tmp = last;
    --tmp;
    while (last != current) {
      std::swap(*tmp, *last);
      --last;
      --tmp;
    }
  }
  if constexpr (sizeof...(args)) {
    for (auto element : {args...}) {
      *current = std::forward<T>(element);
      ++current;
    }
  }
  return result;
}

template <typename T>
template <typename... Args>
void vector<T>::emplace_back(Args &&... args) {
  const_iterator last = cend();
  emplace(last, args...);
}
}  // namespace s21
