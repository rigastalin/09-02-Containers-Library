#include "s21_list.h"

namespace s21 {
template <class T>
list<T>::list() : head_(), tail_(), size_(0) {
  this->head_ = new Node();
  this->tail_ = new Node();
  this->head_->next = this->tail_;
  this->tail_->prev = this->head_;
}

template <class T>
list<T>::list(size_type count) : list() {
  for (size_t i = 0; i < count; ++i) {
    push_front(value_type());
  }
}

template <class T>
list<T>::list(std::initializer_list<value_type> const &items) : list() {
  for (const_reference item : items) {
    push_back(item);
  }
}

template <class T>
list<T>::list(const list &other) : list() {
  Node *pos = other.head_->next;
  while (pos->next != nullptr) {
    push_back(pos->data);
    pos = pos->next;
  }
  size_ = other.size_;
}

template <class T>
list<T>::list(list &&other) : list() {
  operator=(std::move(other));
}

template <class T>
list<T>::~list() {
  clear();
  delete this->tail_;
  delete this->head_;
}

template <class T>
list<T> &list<T>::operator=(list<T> &&other) {
  if (&other == this) return *this;
  this->~list();
  this->head_ = std::exchange(other.head_, nullptr);
  this->tail_ = std::exchange(other.tail_, nullptr);
  this->size_ = std::exchange(other.size_, 0);
  return *this;
}

template <class T>
typename list<T>::const_reference list<T>::front() {
  return head_->next->data;
}

template <class T>
typename list<T>::const_reference list<T>::back() {
  return tail_->prev->data;
}

template <class T>
typename list<T>::iterator list<T>::begin() {
  iterator it(*this);
  ++it;
  return it;
}

template <class T>
typename list<T>::iterator list<T>::end() {
  iterator it(*this);
  while (it.ptr_ != tail_) {
    ++it;
  }
  return it;
}

template <class T>
typename list<T>::const_iterator list<T>::cbegin() const {
  const_iterator it(*this);
  ++it;
  return it;
}

template <class T>
typename list<T>::const_iterator list<T>::cend() const {
  const_iterator it(*this);
  while (it.ptr_ != nullptr) {
    ++it;
  }
  return it;
}

template <class T>
bool list<T>::empty() {
  return this->size_ == 0;
}

template <class T>
typename list<T>::size_type list<T>::size() {
  return this->size_;
}

template <class T>
typename list<T>::size_type list<T>::max_size() const {
  return ((std::numeric_limits<size_type>::max() / sizeof(Node)) / 2);
}

template <class T>
void list<T>::clear() {
  while (!empty()) {
    pop_back();
  }
  size_ = 0;
}

template <class T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node *new_Node = new Node(value);
  new_Node->prev = pos.ptr_->prev;
  new_Node->next = pos.ptr_;
  pos.ptr_->prev->next = new_Node;
  pos.ptr_->prev = new_Node;
  if (pos.ptr_ == head_) head_ = new_Node;
  ++size_;
  return iterator(--pos);
}

template <class T>
void list<T>::erase(iterator pos) {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  if (pos.ptr_ == head_) {
    pop_front();
  } else if (pos.ptr_ == tail_) {
    pop_back();
  } else {
    Node *temp = pos.ptr_;
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    delete temp;
    --size_;
  }
}

template <class T>
void list<T>::push_back(const_reference value) {
  if (size_ >= max_size()) {
    throw std::out_of_range("Size is more than maxsize_");
  }
  Node *new_Node = new Node(value);
  if (head_ == nullptr && tail_ == nullptr) {
    head_ = new_Node;
    tail_ = new_Node;
    tail_->prev = new_Node;
  } else {
    new_Node->prev = tail_->prev;
    new_Node->next = tail_;
    tail_->prev->next = new_Node;
    tail_->prev = new_Node;
  }
  ++size_;
}

template <class T>
void list<T>::push_front(const_reference value) {
  Node *new_Node = new Node(value);
  new_Node->prev = head_;
  new_Node->next = head_->next;
  head_->next->prev = new_Node;
  head_->next = new_Node;
  ++size_;
}

template <class T>
void list<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("list is empty");
  }
  Node *newhead_ = head_->next->next;
  newhead_->prev = head_;
  if (head_->next) delete head_->next;
  head_->next = newhead_;
  size_--;
}

template <class T>
void list<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("list is empty");
  }
  Node *newtail_ = tail_->prev->prev;
  newtail_->next = tail_;
  delete tail_->prev;
  tail_->prev = newtail_;
  size_--;
}

template <class T>
void list<T>::swap(list &other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template <class T>
void list<T>::merge(list &other) {
  if (&other == this) return;
  this->splice(this->cbegin(), other);
  sort();
}

template <class T>
void list<T>::splice(const_iterator pos, list &other) {
  if (&other == this) return;
  if (size_ == 0) {
    head_->next = other.head_->next;
    tail_->prev = other.tail_->prev;
  }
  for (iterator it = other.begin(); it != other.end(); ++it) {
    insert(pos, it.ptr_->data);
  }
}

template <class T>
void list<T>::reverse() {
  if (empty()) {
    throw std::out_of_range("list is empty");
  }
  iterator forward = begin();
  iterator backward = end();
  --backward;
  size_t i = 0;
  while (i < ((size_) / 2)) {
    std::swap(forward.ptr_->data, backward.ptr_->data);
    ++forward;
    --backward;
    ++i;
  }
}

template <class T>
void list<T>::unique() {
  for (auto frst = begin(); frst != end(); ++frst) {
    auto scnd = frst;
    ++scnd;
    while (scnd != end() && *frst == *scnd) {
      auto thrd = scnd;
      ++scnd;
      erase(thrd);
    }
  }
}

template <class T>
void list<T>::sort() {
  if (empty()) {
    throw std::out_of_range("list is empty");
  }
  for (size_t i = 1; i < size_; i++) {
    iterator it = begin();
    for (size_t j = i; j < size_; ++it, ++j)
      if (it.ptr_->next->data < it.ptr_->data) {
        std::swap(it.ptr_->next->data, it.ptr_->data);
      }
  }
}

/* ---------------------LIST ITERATOR--------------------- */
template <class T>
list<T>::ListIterator::ListIterator(const list<T> &other) {
  ptr_ = other.head_;
  tail_ = other.tail_;
}

template <class T>
typename list<T>::ListIterator &list<T>::ListIterator::operator--() {
  if (tail_ == nullptr && ptr_ == nullptr) {
    throw std::out_of_range("List is empty");
  }
  if (ptr_ == nullptr) {
    ptr_ = tail_;
  } else {
    ptr_ = ptr_->prev;
  }
  return *this;
}

template <class T>
typename list<T>::ListIterator &list<T>::ListIterator::operator++() {
  if (ptr_ == nullptr) {
    throw std::out_of_range("List is empty");
  }
  tail_ = ptr_;
  ptr_ = ptr_->next;
  if (ptr_ != nullptr) {
    tail_ = nullptr;
  }
  return *this;
}

template <class T>
typename list<T>::reference list<T>::ListIterator::operator*() {
  if (ptr_ == nullptr) {
    throw std::out_of_range("Error: there is not such element");
  }
  return ptr_->data;
}

template <class T>
bool list<T>::ListIterator::operator!=(const ListIterator &other) {
  return ptr_ != other.ptr_;
}

template <class T>
bool list<T>::ListIterator::operator==(const ListIterator &other) {
  return ptr_ == other.ptr_;
}

/* ---------------------LIST CONST ITERATOR--------------------- */
template <class T>
typename list<T>::ListConstIterator &list<T>::ListConstIterator::operator=(
    const ListIterator &other) {
  this->ptr_ = other.ptr_;
  this->head_ = other.head_;
  this->tail_ = other.tail_;
  return *this;
}

template <class T>
typename list<T>::ListConstIterator &list<T>::ListConstIterator::operator!=(
    const ListIterator &other) {
  this->ptr_ != other.ptr_;
  this->head_ != other.head_;
  this->tail_ != other.tail_;
  return *this;
}

/* ---------------------LIST BONUS-------------------------- */
template <class T>
template <class... Args>
typename list<T>::iterator list<T>::emplace(const_iterator pos,
                                            Args &&...args) {
  for (const_reference value : {args...}) {
    pos = insert(pos, value);
  }
  return pos;
}

template <class T>
template <class... Args>
void list<T>::emplace_back(Args &&...args) {
  for (const_reference value : {args...}) {
    push_back(value);
  }
}

template <class T>
template <class... Args>
void list<T>::emplace_front(Args &&...args) {
  for (const_reference value : {args...}) {
    push_front(value);
  }
}
}  // namespace s21
