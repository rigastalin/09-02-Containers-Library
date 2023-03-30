#include "s21_vector.h"

#include <cmath>
#include <vector>

using namespace s21;

namespace s21 {
//---------------------------------Constructors_and_Destructor-------------------------
template <typename T>
vector<T>::vector() : size_(0), capacity_(0), arr_(nullptr) {}

template <typename T>
vector<T>::vector(size_type n) : size_(n), capacity_(n) {
  n ? arr_ = new T[n]{} : arr_ = nullptr;
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : size_(items.size()), capacity_(size_) {
  arr_ = new T[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    arr_[i] = *it;
    i++;
  }
  size_ = items.size();
  capacity_ = items.size();
}

// destructor
template <typename T>
vector<T>::~vector() {
  if (arr_ != nullptr) {
    delete[] arr_;
  }
}

//---------------------------------Copy_and_Move---------------------------------------
// copy
template <typename T>
vector<T>::vector(const vector &v) : size_(v.size_), capacity_(v.capacity_) {
  arr_ = new value_type[v.capacity_];
  for (size_t i = 0; i < v.size_; ++i) {
    arr_[i] = v.arr_[i];
  }
}

// move
template <typename T>
vector<T>::vector(vector &&v) {
  operator=(std::move(v));
}

//---------------------------------Operator--------------------------------------------
template <typename T>
vector<T> vector<T>::operator=(vector &&v) {
  arr_ = v.arr_;
  size_ = v.size_;
  capacity_ = v.capacity_;

  v.arr_ = nullptr;
  v.size_ = 0;
  v.capacity_ = 0;

  return *this;
}

//---------------------------------Vector_Element_Access----------------------------------------
template <typename T>
T &vector<T>::at(size_type i) {
  if (i >= size_) {
    throw std::out_of_range("Index is out of range");
  }
  return arr_[i];
}

template <typename T>
T &vector<T>::operator[](size_type i) {
  return at(i);
}

template <typename T>
const T &vector<T>::front() {
  return at(0);
}

template <typename T>
const T &vector<T>::back() {
  return *(end() - 1);
}

template <typename T>
T *vector<T>::data() {
  return arr_;
}

//---------------------------------Vector_Iterators----------------------------------------
template <typename T>
T *vector<T>::begin() {
  return arr_;
}

template <typename T>
T *vector<T>::end() {
  return arr_ + size_;
}
//---------------------------------Vector_Capacity----------------------------------------
template <typename T>
bool vector<T>::empty() {
  return !size_ ? true : false;
}

template <typename T>
size_t vector<T>::size() {
  return size_;
}

template <typename T>
size_t vector<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(T) / 2;
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size <= capacity_) {
    throw std::out_of_range("Value must be more than capacity of the vector");
  }
  resize(size);
}

template <typename T>
size_t vector<T>::capacity() {
  return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (capacity_ == size_) {
    throw std::out_of_range("All memory is in use. Can't fit vector");
  }
  resize(size_);
}

//---------------------------------Vector_Modifiers----------------------------------------

template <typename T>
void vector<T>::clear() {
  size_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_t pos_index = pos - begin();
  if (pos_index > size_) {
    throw std::out_of_range("Index is out of range");
  }
  if (size_ == capacity_) {
    reserve(capacity_ * 2);
  }
  size_type count = size_++;
  for (; count > pos_index; --count) {
    arr_[count] = arr_[count - 1];
  }
  arr_[count--] = value;
  return begin() + pos_index;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  for (size_type i = pos - begin(); i < size_ - 1; ++i) {
    arr_[i] = arr_[i + 1];
  }
  pop_back();
}

template <typename T>
void vector<T>::push_back(const_reference v) {
  insert(end(), v);
}

template <typename T>
void vector<T>::pop_back() {
  --size_;
  (arr_ + size_)->~T();
}

template <typename T>
void vector<T>::swap(vector &other) {
  std::swap(arr_, other.arr_);
  std::swap(capacity_, other.capacity_);
  std::swap(size_, other.size_);
}

//---------------------------------SubFunc----------------------------------------
template <typename T>
void vector<T>::PrintVector() {
  if (arr_) {
    for (auto i = 0; i < (int)size_; i++) {
      std::cout << arr_[i];
    }
    std::cout << std::endl;
    std::cout << "Size of vector === " << size_ << std::endl;
    std::cout << "Capacity of vector === " << capacity_ << std::endl;
    std::cout << "-----------------------------------" << std::endl;
  } else {
    std::cout << "Vector is empty" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
  }
}

template <typename T>
void vector<T>::resize(size_type size) {
  T *buf = new T[size];
  for (size_t i = 0; i < size_; ++i) {
    buf[i] = arr_[i];
  }
  delete[] arr_;
  arr_ = buf;
  capacity_ = size;
}

//---------------------------------Vector_Bonus----------------------------------------
template <class T>
template <class... Args>
typename vector<T>::iterator vector<T>::emplace(const_iterator pos,
                                                Args &&...args) {
  iterator it = iterator(pos);
  for (auto value : {args...}) {
    it = insert(it, value);
    ++it;
  }
  return --it;
}

template <class T>
template <class... Args>
void vector<T>::emplace_back(Args &&...args) {
  for (const_reference value : {args...}) {
    push_back(value);
  }
}

}  // namespace s21
