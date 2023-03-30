#ifndef SRC_S21_ARRAY_H_
#define SRC_S21_ARRAY_H_

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace s21 {
template <class T, std::size_t N>
class array {
 private:
  T data_[N];

 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  /*-------------------------ARRAY CONSTRUCTORS------------------------- */
  array() {}
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a);

  /*-------------------------ARRAY DECONSTRUCTORS----------------------- */
  ~array() {}

  /*-------------------------ARRAY OPERATORS---------------------------- */
  array &operator=(array &&a);

  /*-------------------------ARRAY ELEMENT ACCESS----------------------- */
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  /*-------------------------ARRAY ITERATORS---------------------------- */
  iterator begin();
  iterator end();

  /*-------------------------ARRAY CAPACITY---------------------------- */
  bool empty();
  size_type size();
  size_type max_size();

  /*-------------------------ARRAY MODIFIERS---------------------------- */
  void swap(array &other);
  void fill(const_reference value);
};
}  // namespace s21
#endif  // SRC_S21_ARRAY_H_
