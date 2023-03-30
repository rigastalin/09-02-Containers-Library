#include "s21_queue.h"

namespace s21 {
template <class T>
queue<T>::queue(std::initializer_list<value_type> const &items) {
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
queue<T>::queue(const queue &q) : queue() {
  if (q.empty()) {
    head_ = nullptr;
    tail_ = nullptr;
  } else {
    Node *pos = q.head_;
    Node *temp = new Node(pos->data);
    head_ = temp;
    tail_ = temp;
    while (pos->next != nullptr) {
      pos = pos->next;
      temp = new Node(pos->data);
      tail_->next = temp;
      tail_ = temp;
    }
  }
  size_ = q.size_;
}

template <class T>
queue<T>::queue(queue &&q) {
  head_ = nullptr;
  operator=(std::move(q));
}

template <class T>
queue<T>::~queue() {
  while (!empty()) {
    pop();
  }
  size_ = 0;
}

template <class T>
size_t queue<T>::size() {
  return size_;
}

template <class T>
bool queue<T>::empty() const {
  return head_ == nullptr;
}

template <class T>
queue<T> &queue<T>::operator=(queue<T> &&other) {
  if (this == &other) {
    return *this;
  } else {
    this->head_ = std::exchange(other.head_, nullptr);
    this->tail_ = std::exchange(other.tail_, nullptr);
    this->size_ = std::exchange(other.size_, 0);
    return *this;
  }
}

template <class T>
void queue<T>::push(const_reference value) {
  if (empty()) {
    head_ = new Node(value);
    tail_ = head_;
  } else {
    Node *temp = new Node(value);
    tail_->next = temp;
    tail_ = tail_->next;
  }
  size_++;
}

template <class T>
void queue<T>::pop() {
  if (empty()) {
    throw std::length_error("It's empty");
  }
  Node *temp = head_;
  head_ = head_->next;
  delete temp;
  size_--;
}

template <class T>
void queue<T>::swap(queue &other) {
  std::swap(size_, other.size_);
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
}

template <class T>
template <class... Args>
void queue<T>::emplace_back(Args &&...args) {
  for (const_reference value : {args...}) {
    push(value);
  }
}
}  // namespace s21
