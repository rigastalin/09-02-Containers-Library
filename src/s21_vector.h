#pragma once

#include <initializer_list>
#include <iostream>
#include <utility>

namespace s21 {

template <class T>
class vector {
 public:
  //---------------------------------SubFunc---------------------------------------------
  void PrintVector();
  //---------------------------------Vector_Member_Types----------------------------------------
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  //---------------------------------Vector_Member_Functions--------------------------
  // constructors
  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  ~vector();

  // copy and move
  vector(const vector &v);
  vector(vector &&v);

  // operator
  vector operator=(vector &&v);

  //---------------------------------Vector_Element_Access----------------------------------------
  reference at(size_type i);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  T *data();

  //---------------------------------Vector_Iterators----------------------------------------
  iterator begin();
  iterator end();

  //---------------------------------Vector_Capacity----------------------------------------
  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  //---------------------------------Vector_Modifiers----------------------------------------
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  //---------------------------------Vector_Bonus--------------------------------------------
  template <class... Args>
  iterator emplace(const_iterator pos, Args &&...args);

  template <class... Args>
  void emplace_back(Args &&...args);

 private:
  size_t size_ = 0;
  size_t capacity_ = 0;
  T *arr_ = nullptr;

  void resize(size_type size);
};
}  // namespace s21
