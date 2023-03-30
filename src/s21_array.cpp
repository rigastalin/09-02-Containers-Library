#include "s21_array.h"

namespace s21 {
template <class T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  if (items.size() > N) {
    throw std::out_of_range("It's out of range");
  }
  size_t i = 0;
  for (auto it = items.begin(); i < N; it++) {
    if (i < items.size()) {
      data_[i++] = *it;
    } else {
      data_[i++] = 0;
    }
  }
}

template <class T, std::size_t N>
array<T, N>::array(const array &a) {
  if (N < this->size()) {
    throw std::out_of_range("Not enough space");
  }
  std::copy(a.data_, a.data_ + N, data_);
}

template <class T, std::size_t N>
array<T, N>::array(array &&a) {
  if (N < a.size()) {
    throw std::out_of_range("Not enough space");
  }
  std::move(a.data_, a.data_ + N, data_);
}

template <class T, std::size_t N>
array<T, N> &array<T, N>::operator=(array<T, N> &&a) {
  for (size_type i = 0; i < N; i++) {
    this[i] = a.data_[i];
    at[i] = a.at(i);
  }
  return *this;
}

template <class T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  return this->data_[pos];
}

template <class T, std::size_t N>
typename array<T, N>::reference &array<T, N>::operator[](
    array<T, N>::size_type pos) {
  return this->data_[pos];
}

template <class T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() {
  return data_[0];
}

template <class T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() {
  return data_[this->size() - 1];
}

template <class T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return data_;
}

template <class T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return data_;
}

template <class T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return &this->data_[this->size()];
}

template <class T, std::size_t N>
bool array<T, N>::empty() {
  return N == 0 ? 1 : 0;
}

template <class T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() {
  return N;
}

template <class T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() {
  return N;
}

template <class T, std::size_t N>
void array<T, N>::swap(array &other) {
  std::swap(this->data_, other.data_);
}

template <class T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_t i = 0; i < size(); i++) {
    at(i) = value;
  }
}

}  // namespace s21
