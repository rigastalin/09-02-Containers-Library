#include "s21_map.h"

namespace s21 {
template <class Key, class T>
map<Key, T>::map(const map& other) {
  size_ = other.size_;
  Tree(other.head_);
}

template <class Key, class T>
map<Key, T>::map(map&& other) : size_(other.size_), head_(other.head_) {
  other.size_ = 0;
  other.head_ = nullptr;
}

template <class Key, class T>
map<Key, T>::map(std::initializer_list<value_type> const& items) {
  auto it = items.begin();
  while (it != items.end()) {
    insert(*it);
    ++it;
  }
}

template <class Key, class T>
map<Key, T>::~map() {
  TreeDel(head_);
}

template <class Key, class T>
void map<Key, T>::operator=(map&& other) {
  if (&other != this) {
    size_ = other.size_;
    Tree(other.head_);
  }
}

template <class Key, class T>
T& map<Key, T>::at(const Key& key) {
  MapNode<Key, T>* node = head_;
  while (key != node->key) {
    if (key < node->key) {
      if (node->left == nullptr)
        throw std::out_of_range("Map is out of range");
      else
        node = node->left;
    } else {
      if (node->right == nullptr)
        throw std::out_of_range("Map is out of range");
      else
        node = node->right;
    }
  }
  return node->value;
}

template <class Key, class T>
T& map<Key, T>::operator[](const Key& key) {
  if (contains(key)) {
    return at(key);
  } else {
    std::pair<iterator, bool> it_pair = insert(key, T());
    iterator it = it_pair.first;
    return it.second();
  }
}

template <class Key, class T>
typename map<Key, T>::iterator map<Key, T>::begin() {
  MapNode<Key, T>* node = head_;
  while (node != nullptr && node->left != nullptr) node = node->left;
  return iterator(node);
}

template <class Key, class T>
void map<Key, T>::clear() {
  TreeDel(head_);
  head_ = nullptr;
  size_ = 0;
}

template <class Key, class T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type& value) {
  return insert(value.first, value.second);
}

template <class Key, class T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key& key, const T& obj) {
  if (size_ >= max_size()) return std::make_pair(iterator(nullptr), false);

  MapNode<Key, T>* node = new MapNode<Key, T>(key, obj);
  std::pair<iterator, bool> pair_res = std::make_pair(iterator(node), true);

  size_ += 1;

  if (head_ == nullptr) {
    head_ = node;
  } else {
    MapNode<Key, T>* temp = head_;
    while (temp != nullptr) {
      if (key < temp->key) {
        if (temp->left == nullptr) {
          temp->left = node;
          node->parent = temp;
          break;
        } else {
          temp = temp->left;
        }
      } else if (key > temp->key) {
        if (temp->right == nullptr) {
          temp->right = node;
          node->parent = temp;
          break;
        } else {
          temp = temp->right;
        }
      } else {
        size_ -= 1;
        pair_res = std::make_pair(iterator(nullptr), false);
        delete node;
        break;
      }
    }
  }
  return pair_res;
}

template <class Key, class T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key& key, const T& obj) {
  if (size_ >= max_size()) return std::make_pair(iterator(nullptr), false);

  MapNode<Key, T>* node = new MapNode<Key, T>(key, obj);
  std::pair<iterator, bool> pair_result = std::make_pair(iterator(node), true);
  size_ += 1;
  if (head_ == nullptr) {
    head_ = node;
  } else {
    MapNode<Key, T>* temp = head_;
    while (temp != nullptr) {
      if (key < temp->key) {
        if (temp->left == nullptr) {
          temp->left = node;
          node->parent = temp;
          break;
        } else {
          temp = temp->left;
        }
      } else if (key > temp->key) {
        if (temp->right == nullptr) {
          temp->right = node;
          node->parent = temp;
          break;
        } else {
          temp = temp->right;
        }
      } else {
        temp->value = node->value;
        pair_result = std::make_pair(iterator(temp), true);
        size_ -= 1;
        delete node;
        break;
      }
    }
  }
  return pair_result;
}

template <class Key, class T>
void map<Key, T>::erase(iterator pos) {
  // if (empty()) {
  //     throw std::out_of_range("Map is empty");
  // }

  MapNode<Key, T>* node = head_;
  while (node != nullptr && node->key != pos.first()) {
    if (node->key > pos.first()) {
      node = node->left;
    } else {
      node = node->right;
    }
  }

  if (node != nullptr) {
    if (node->left == nullptr && node->right == nullptr) {
      if (node->parent != nullptr) {
        if (node->parent->left == node) {
          node->parent->left = nullptr;
        }
        if (node->parent->right == node) {
          node->parent->right = nullptr;
        }
      } else {
        head_ = nullptr;
      }
    } else if (node->left == nullptr) {
      if (node->parent != nullptr) {
        if (node->parent->left == node) {
          node->parent->left = node->right;
        }
        if (node->parent->right == node) {
          node->parent->right = node->right;
        }
        node->right->parent = node->parent;
      } else {
        node->right->parent = nullptr;
        head_ = node->right;
      }
    } else if (node->right == nullptr) {
      if (node->parent != nullptr) {
        if (node->parent->left == node) {
          node->parent->left = node->left;
        }
        if (node->parent->right == node) {
          node->parent->right = node->left;
        }
        node->left->parent = node->parent;
      } else {
        node->left->parent = nullptr;
        head_ = node->left;
      }
    } else {
      MapNode<Key, T>* temp = node->right;
      while (temp->left != nullptr) {
        temp = temp->left;
      }
      temp->left = node->left;
      temp->left->parent = temp;
      if (node->parent != nullptr) {
        if (node->parent->left == node) {
          node->parent->left = node->right;
        }
        if (node->parent->right == node) {
          node->parent->right = node->right;
        }
        node->right->parent = node->parent;
      } else {
        node->right->parent = nullptr;
        head_ = node->right;
      }
    }
    size_ -= 1;
    delete node;
  }
}

template <class Key, class T>
void map<Key, T>::swap(map& other) {
  if (&other != this) {
    std::swap(head_, other.head_);
    std::swap(size_, other.size_);
  }
}

template <class Key, class T>
void map<Key, T>::merge(map& other) {
  iterator it = other.begin();
  while (it != other.end()) {
    if (!contains(it.first())) {
      insert(it.first(), it.second());
      other.erase(it);
      it = other.begin();
    } else {
      ++it;
    }
  }
}

template <class Key, class T>
bool map<Key, T>::contains(const Key& key) {
  MapNode<Key, T>* node = head_;
  while (node != nullptr && node->key != key) {
    if (node->key > key) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return node != nullptr;
}
}  //  namespace s21
