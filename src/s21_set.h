#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <utility>

namespace s21 {
template <class Key>
class SetNode {
 public:
  SetNode* parent = nullptr;
  SetNode* left = nullptr;
  SetNode* right = nullptr;

  Key value;
  explicit SetNode(const Key& value) : value(value) {}
};

template <class Key>
class SetIterator {
 public:
  explicit SetIterator(SetNode<Key>* node) : node(node) {}

  Key& value() const { return node->value; }

  void operator++() { add(); }
  void operator++(int) { add(); }
  void operator--() { min(); }
  void operator--(int) { min(); }
  bool operator==(const SetIterator& other) { return node == other.node; }
  bool operator!=(const SetIterator& other) { return node != other.node; }

 protected:
  SetNode<Key>* node;

 private:
  void add() {
    if (node == nullptr) return;
    if (node->right != nullptr) {
      node = node->right;
      while (node->left != nullptr) {
        node = node->left;
      }
    } else {
      if (node->parent != nullptr && node->parent->right == node) {
        while (node->parent != nullptr && node->parent->left != node) {
          node = node->parent;
        }
      }
      node = node->parent;
    }
  }

  void min() {
    if (node == nullptr) return;
    if (node->left != nullptr) {
      node = node->left;
      while (node->right != nullptr) {
        node = node->right;
      }
    } else {
      if (node->parent != nullptr && node->parent->left == node) {
        while (node->parent != nullptr && node->parent->right != node) {
          node = node->parent;
        }
        node = node->parent;
      }
    }
  }
};

template <class Key>
class SetConstIterator : public SetIterator<Key> {
 public:
  explicit SetConstIterator(SetNode<Key>* node) : SetIterator<Key>(node) {}
  const Key value() const { return SetIterator<Key>::node->value; }
  bool operator==(const SetConstIterator& other) {
    return SetIterator<Key>::node == other.node;
  }
  bool operator!=(const SetConstIterator& other) {
    return SetIterator<Key>::node != other.node;
  }
};

template <class Key>
class set {
 public:
  using value_type = Key;
  using key_type = Key;
  using size_type = size_t;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = SetIterator<Key>;
  using const_iterator = SetConstIterator<Key>;

 public:
  /*-------------------------SET CONSTRUCTORS------------------------- */
  set() {}
  explicit set(std::initializer_list<value_type> const& items);
  set(const set& other);
  set(set&& other);
  void operator=(set&& other);

  /*-------------------------SET DECONSTRUCTORS----------------------- */
  ~set();

  /*-------------------------SET ITERATORS---------------------------- */
  iterator begin();
  iterator end() { return iterator(nullptr); }

  const_iterator cbegin() { return begin(); }
  const_iterator cend() { return end(); }

  /*-------------------------SET CAPACITY----------------------------- */
  bool empty() { return size_ == 0; }
  size_type size() { return size_; }
  size_type max_size() {
    return ((std::numeric_limits<size_type>::max() / sizeof(SetNode<Key>)) / 2);
  }

  /*-------------------------SET MODIFIERS---------------------------- */
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(set& other);
  void merge(set& other);

  /*-------------------------SET LOOKUP------------------------------- */
  iterator find(const Key& value);
  bool contains(const Key& value);

  /*-------------------------SET BONUS-------------------------------- */
  template <class... Args>
  std::pair<iterator, bool> emplace(Args&&... args) {
    return (insert(args), ...);
  }

 private:
  size_type size_ = 0;
  SetNode<Key>* head_ = nullptr;

  void Tree(SetNode<Key>* node) {
    if (node == nullptr) return;

    insert(node->value);

    if (node->left != nullptr) Tree(node->left);
    if (node->right != nullptr) Tree(node->right);
  }

  void DelTree(SetNode<Key>* node) {
    if (node == nullptr) return;

    if (node->left != nullptr) DelTree(node->left);
    if (node->right != nullptr) DelTree(node->right);

    delete node;
  }
};
}  // namespace s21
#endif  // SRC_S21_SET_H_
