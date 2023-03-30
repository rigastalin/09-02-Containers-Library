#include "s21_stack.h"

namespace s21 {
template <class T>
stack<T>::stack(std::initializer_list<value_type> const &items) {
  head_ = nullptr;
  size_ = 0;
  auto i = items.begin();
  while (i < items.end()) {
    this->push(*i);
    i++;
  }
  this->size_ = items.size();
}

template <class T>
stack<T>::stack(const stack &q) : stack() {
  if (q.empty()) {
    head_ = nullptr;
  } else {
    Node *pos = q.head_;
    Node *temp = new Node(pos->data);
    head_ = temp;
    Node *_tail = temp;
    while (pos->next != nullptr) {
      pos = pos->next;
      temp = new Node(pos->data);
      _tail->next = temp;
      _tail = temp;
    }
  }
  size_ = q.size_;
}

template <class T>
stack<T>::stack(stack &&q) {
  head_ = nullptr;
  operator=(std::move(q));
}

template <class T>
stack<T>::~stack() {
  while (!empty()) {
    pop();
  }
  size_ = 0;
}

template <class T>
stack<T> &stack<T>::operator=(stack<T> &&other) {
  if (this == &other) {
    return *this;
  } else {
    this->head_ = std::exchange(other.head_, nullptr);
    this->size_ = std::exchange(other.size_, 0);
    return *this;
  }
}

template <class T>
typename stack<T>::const_reference stack<T>::top() {
  return head_->data;
}

template <class T>
bool stack<T>::empty() const {
  return head_ == nullptr;
}

template <class T>
typename stack<T>::size_type stack<T>::size() {
  return size_;
}

template <class T>
void stack<T>::push(const_reference value) {
  if (empty()) {
    head_ = new Node(value);
  } else {
    Node *temp = new Node(value);
    temp->data = value;
    temp->next = head_;
    head_ = temp;
  }
  size_++;
}

template <class T>
void stack<T>::pop() {
  if (empty()) {
    throw std::length_error("It's empty");
  }
  Node *temp = head_;
  head_ = head_->next;
  delete temp;
  size_--;
}

template <class T>
void stack<T>::swap(stack &other) {
  std::swap(head_, other.head_);
  std::swap(size_, other.size_);
}

template <class T>
template <class... Args>
void stack<T>::emplace_front(Args &&...args) {
  for (const_reference value : {args...}) {
    push(value);
  }
}
}  // namespace s21
