#ifndef SRC_S21_MULTISET_H_
#define SRC_S21_MULTISET_H_

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <utility>

namespace s21 {
template <class Key>
class MultiNode {
 public:
  MultiNode* parent = nullptr;
  MultiNode* left = nullptr;
  MultiNode* right = nullptr;

  Key value;

  explicit MultiNode(const Key& value) : value(value) {}
};

template <class Key>
class MultisetIterator {
 public:
  explicit MultisetIterator(MultiNode<Key>* node) : node(node) {}

  Key& value() const { return node->value; }

  void operator++() { add(); }
  void operator++(int) { add(); }
  void operator--() { min(); }
  void operator--(int) { min(); }
  bool operator==(const MultisetIterator& other) { return node == other.node; }
  bool operator!=(const MultisetIterator& other) { return node != other.node; }

 protected:
  MultiNode<Key>* node;

 private:
  void add() {
    if (node == nullptr) return;
    if (node->right != nullptr) {
      node = node->right;
      while (node->left != nullptr) node = node->left;
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
      while (node->right != nullptr) node = node->right;
    } else {
      if (node->parent != nullptr && node->parent->left == node) {
        while (node->parent != nullptr && node->parent->right != node) {
          node = node->parent;
        }
      }
      node = node->parent;
    }
  }
};

template <class Key>
class MultiConstIterator : public MultisetIterator<Key> {
 public:
  explicit MultiConstIterator(MultiNode<Key>* node)
      : MultisetIterator<Key>(node) {}

  const Key valut() const { return MultisetIterator<Key>::node->value; }

  bool operator==(const MultiConstIterator& other) {
    return MultisetIterator<Key>::node == other.node;
  }
  bool operator!=(const MultiConstIterator& other) {
    return MultisetIterator<Key>::node != other.node;
  }
};

template <class Key>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = MultisetIterator<Key>;
  using const_iterator = MultiConstIterator<Key>;
  using size_type = size_t;

 public:
  /*-------------------------MULTISET CONSTRUCTORS--------------------- */
  multiset() {}
  explicit multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& other);
  multiset(multiset&& other);
  void operator=(multiset&& other);

  /*-------------------------MULTISET DECONSTRUCTORS----------------------- */
  ~multiset();

  /*-------------------------MULTISET ITERATORS---------------------------- */
  iterator begin();
  iterator end() { return iterator(nullptr); }

  const_iterator cbegin() { return begin(); }
  const_iterator cend() { return end(); }

  /*-------------------------MULTISET CAPACITY----------------------------- */
  bool empty() { return size_ == 0; }
  size_type size() { return size_; }
  size_type max_size() {
    return ((std::numeric_limits<size_type>::max() / sizeof(MultiNode<Key>)) /
            2);
  }

  /*-------------------------MULTISET MODIFIERS---------------------------- */
  void clear();
  iterator insert(const value_type& value);
  void erase(iterator pos);
  void swap(multiset& other);
  void merge(multiset& other);

  /*-------------------------MULTISET LOOKUP------------------------------- */
  size_type count(const Key& value);
  iterator find(const Key& value);
  bool contains(const Key& value);
  std::pair<iterator, iterator> equal_range(const Key& value);
  iterator lower_bound(const Key& value);
  iterator upper_bound(const Key& value);

  /*-------------------------MULTISET BONUS-------------------------------- */
  template <class... Args>
  iterator emplace(Args&&... args) {
    return (insert(args), ...);
  }

 private:
  MultiNode<Key>* head_ = nullptr;
  size_type size_ = 0;

  void Tree(MultiNode<Key>* node) {
    if (node == nullptr) return;
    insert(node->value);
    if (node->left != nullptr) Tree(node->left);
    if (node->right != nullptr) Tree(node->right);
  }

  void DelTree(MultiNode<Key>* node) {
    if (node == nullptr) return;
    if (node->left != nullptr) DelTree(node->left);
    if (node->right != nullptr) DelTree(node->right);
    delete node;
  }
};
}  // namespace s21
#endif  //  SRC_S21_MULTISET_H_
