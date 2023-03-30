#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_

#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {

template <class Key, class T>
class MapNode {
 public:
  MapNode* parent = nullptr;
  MapNode* left = nullptr;
  MapNode* right = nullptr;
  const Key key;
  T value;
  MapNode(Key key, const T& value) : key(key), value(value) {}
};

template <class Key, class T>
class MapIterator {
 public:
  explicit MapIterator(MapNode<Key, T>* node) : node(node) {}

  const Key first() const { return node->key; }
  T& second() { return node->value; }

  void operator++() { add(); }
  void operator++(int) { add(); }
  void operator--() { min(); }
  void operator--(int) { min(); }
  bool operator==(const MapIterator& other) { return node == other.node; }
  bool operator!=(const MapIterator& other) { return node != other.node; }

 protected:
  MapNode<Key, T>* node;

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
      while (node->right != nullptr) node = node->right;
    } else {
      if (node->parent != nullptr && node->parent->left == node)
        while (node->parent != nullptr && node->parent->right != node)
          node = node->parent;
      node = node->parent;
    }
  }
};

template <class Key, class T>
class MapConstIterator : public MapIterator<Key, T> {
 public:
  explicit MapConstIterator(MapNode<Key, T>* node)
      : MapIterator<Key, T>(node) {}

  const Key first() const { return MapIterator<Key, T>::node->key; }
  const T second() const { return MapIterator<Key, T>::node->value; }

  bool operator==(const MapConstIterator& other) {
    return MapIterator<Key, T>::node == other.node;
  }
  bool operator!=(const MapConstIterator& other) {
    return MapIterator<Key, T>::node != other.node;
  }
};

template <class Key, class T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = MapIterator<Key, T>;
  using const_iterator = MapIterator<Key, T>;
  using size_type = size_t;

 public:
  /*-------------------------MAP CONSTRUCTORS------------------------- */
  map() {}
  explicit map(std::initializer_list<value_type> const& items);
  map(const map& other);
  map(map&& other);
  void operator=(map&& other);

  /*-------------------------MAP CONSTRUCTORS------------------------- */
  ~map();

  /*-------------------------MAP ELEMENT ACCESS----------------------- */
  T& at(const Key& key);
  T& operator[](const Key& key);

  /*-------------------------MAP ITERATORS---------------------------- */
  iterator begin();
  iterator end() { return iterator(nullptr); }

  /*-------------------------MAP CAPACITY----------------------------- */
  bool empty() { return size_ == 0; }
  size_type size() { return size_; }
  size_type max_size() {
    return ((std::numeric_limits<size_type>::max() / sizeof(MapNode<Key, T>)) /
            2);
  }

  /*-------------------------MAP MODIFIERS--------------------------- */
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);

  /*-------------------------MAP LOOKUP------------------------------ */
  bool contains(const Key& key);

  /*-------------------------BONUS----------------------------------- */
  template <class... Args>
  std::pair<iterator, bool> emplace(Args&&... args) {
    return (insert(args), ...);
  }

 private:
  size_type size_ = 0;
  MapNode<Key, T>* head_ = nullptr;

  void Tree(MapNode<Key, T>* node) {
    if (node == nullptr) return;
    insert(node->key, node->value);
    if (node->left != nullptr) Tree(node->left);
    if (node->right != nullptr) Tree(node->right);
  }

  void TreeDel(MapNode<Key, T>* node) {
    if (node == nullptr) return;
    if (node->left != nullptr) TreeDel(node->left);
    if (node->right != nullptr) TreeDel(node->right);

    delete node;
  }
};
}  // namespace s21
#endif  // SRC_S21_MAP_H_
