#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace s21 {
template <class T>
class stack {
 private:
  struct Node {
    T data;
    Node *next;
    Node() {}
    explicit Node(const T &val, Node *n = nullptr) : data(val), next(n) {}
  };
  Node *head_;
  size_t size_;

 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  /*-------------------------STACK CONSTRUCTORS------------------------- */
  stack() : head_(nullptr), size_(0U) {}
  explicit stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s);

  /*-------------------------STACK DECONSTRUCTORS----------------------- */
  ~stack();

  /*-------------------------STACK OPERATORS---------------------------- */
  stack &operator=(stack &&other);

  /*-------------------------STACK ELEMENT ACCESS----------------------- */
  const_reference top();

  /*-------------------------STACK CAPACITY----------------------------- */
  bool empty() const;
  size_type size();

  /*-------------------------STACK MODIFIERS---------------------------- */
  void push(const_reference value);
  void pop();
  void swap(stack &other);

  /*-------------------------STACK BONUS-------------------------------- */
  template <class... Args>
  void emplace_front(Args &&...args);
};
}  // namespace s21
#endif  // SRC_S21_STACK_H_
