#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {
template <class T>
class list {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

 private:
  struct Node {
    value_type data;
    Node *prev;
    Node *next;
    Node() : data(), prev(nullptr), next(nullptr) {}
    explicit Node(const T &value, Node *n_prev = nullptr,
                  Node *n_next = nullptr) {
      this->data = value;
      this->prev = n_prev;
      this->next = n_next;
    }
    Node &operator=(const Node &other) {
      if (this != &other) {
        this->data = other.data;
        this->prev = other.prev;
        this->next = other.next;
      }
      return *this;
    }
  };
  Node *head_;
  Node *tail_;
  size_t size_;

 public:
  /*-------------------------LIST CONSTRUCTORS------------------------- */
  list();
  list(size_type count);
  list(std::initializer_list<value_type> const &items);
  list(const list &other);
  list(list &&other);

  /*-------------------------LIST DECONSTRUCTORS----------------------- */
  ~list();

  /*-------------------------LIST OPERATORS---------------------------- */
  list &operator=(list &&other);

  /*-------------------------LIST ELEMENT ACCESS----------------------- */
  const_reference front();
  const_reference back();

  /*-------------------------LIST CAPACITY----------------------------- */
  bool empty();
  size_type size();
  size_type max_size() const;

  /*-------------------------LIST MODIFIERS---------------------------- */
  void clear();

  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);

  void reverse();
  void unique();
  void sort();

  /*-------------------------LIST ITERATOR---------------------------- */
 public:
  class ListIterator {
   public:
    Node *head_;
    Node *tail_;
    Node *ptr_;
    ListIterator() : ptr_(nullptr), head_(nullptr), tail_(nullptr) {}
    ListIterator(const list<T> &other);
    ListIterator &operator--();
    ListIterator &operator++();
    reference operator*();
    bool operator!=(const ListIterator &other);
    bool operator!=(const size_type &other) { return ptr_->data != other; };
    bool operator==(const ListIterator &other);
  };

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator() : ListIterator() {}
    ListConstIterator(const list<T> &other) : ListIterator(other) {}
    ListConstIterator &operator=(const ListIterator &other);
    ListConstIterator &operator!=(const ListIterator &other);
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  /*-------------------------LIST ITERATORS---------------------------- */
  iterator begin();
  iterator end();

  const_iterator cbegin() const;
  const_iterator cend() const;
  /*-------------------------LIST MODIFIERS---------------------------- */
  iterator insert(iterator pos, const_reference value);
  void splice(const_iterator pos, list &other);
  void erase(iterator pos);

  /*-------------------------LIST BONUS------------------------------- */
  template <class... Args>
  iterator emplace(const_iterator pos, Args &&...args);

  template <class... Args>
  void emplace_back(Args &&...args);

  template <class... Args>
  void emplace_front(Args &&...args);
};
}  // namespace s21
#endif  // SRC_S21_LIST_H_
