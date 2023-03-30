#ifndef SRC_S21_QUEUE_H_
#define SRC_S21_QUEUE_H_

#include <iostream>
#include <limits>
#include <memory>
#include <utility>

namespace s21 {
template <class T>
class queue {
 private:
  struct Node {
    T data;
    Node *next;
    Node() {}
    explicit Node(const T &val, Node *n = nullptr) : data(val), next(n) {}
  };
  Node *head_;
  Node *tail_;
  size_t size_;

 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  /*-------------------------QUEUE CONSTRUCTORS--------------------- */
  queue() : head_(nullptr), tail_(nullptr), size_(0U) {}
  explicit queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q);

  /*-------------------------QUEUE DECONSTRUCTOR------------ */
  ~queue();

  /*-------------------------QUEUE OPERATORS---------------- */
  queue &operator=(queue &&q);

  /*-----------------------QUEUE ELEMENT ACCESS------------- */
  const_reference front() const { return head_->data; }
  const_reference back() const { return tail_->data; }

  /*-----------------------QUEUE CAPACITY------------------- */
  bool empty() const;
  size_type size();

  /*-----------------------QUEUE MODIFIERS------------------- */
  void push(const_reference value);
  void pop();
  void swap(queue &other);

  /*-----------------------QUEUE BONUS----------------------- */
  template <class... Args>
  void emplace_back(Args &&...args);
};
}  // namespace s21
#endif  // SRC_S21_QUEUE_H_
