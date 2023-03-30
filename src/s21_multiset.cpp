#include "s21_multiset.h"

namespace s21 {
template <class Key>
multiset<Key>::multiset(std::initializer_list<value_type> const& items) {
  auto it = items.begin();
  while (it != items.end()) {
    insert(*it);
    it++;
  }
}

template <class Key>
multiset<Key>::multiset(const multiset& other) {
  size_ = other.size_;
  Tree(other.head_);
}

template <class Key>
multiset<Key>::multiset(multiset&& other) {
  size_ = other.size_;
  head_ = other.head_;
  other.size_ = 0;
  other.head_ = nullptr;
}

template <class Key>
void multiset<Key>::operator=(multiset&& other) {
  if (&other != this) {
    size_ = other.size_;
    Tree(other.head_);
  }
}

template <class Key>
multiset<Key>::~multiset() {
  DelTree(head_);
}

template <class Key>
typename multiset<Key>::iterator multiset<Key>::begin() {
  MultiNode<Key>* node = head_;
  while (node != nullptr && node->left != nullptr) {
    node = node->left;
  }
  return iterator(node);
}

template <class Key>
void multiset<Key>::clear() {
  DelTree(head_);
  head_ = nullptr;
  size_ = 0;
}

template <class Key>
typename multiset<Key>::iterator multiset<Key>::insert(
    const value_type& value) {
  if (size_ >= max_size()) {
    return iterator(nullptr);
  }
  MultiNode<Key>* node = new MultiNode<Key>(value);
  size_ += 1;
  if (head_ == nullptr) {
    head_ = node;
  } else {
    MultiNode<Key>* temp = head_;
    while (temp != nullptr) {
      if (value < temp->value) {
        if (temp->left == nullptr) {
          temp->left = node;
          node->parent = temp;
          break;
        } else {
          temp = temp->left;
        }
      } else if (value > temp->value) {
        if (temp->right == nullptr) {
          temp->right = node;
          node->parent = temp;
          break;
        } else {
          temp = temp->right;
        }
      } else {
        if (temp->right != nullptr) {
          temp->right->parent = node;
          node->right = temp->right;
        }
        temp->right = node;
        node->parent = temp;
        break;
      }
    }
  }
  return iterator(node);
}

template <class Key>
void multiset<Key>::erase(iterator pos) {
  MultiNode<Key>* node = head_;
  while (node != nullptr && node->value != pos.value()) {
    if (node->value > pos.value())
      node = node->left;
    else
      node = node->right;
  }
  if (node != nullptr) {
    if (node->left == nullptr && node->right == nullptr) {
      if (node->parent != nullptr) {
        if (node->parent->left == node) node->parent->left = nullptr;
        if (node->parent->right == node) node->parent->right = nullptr;
      } else {
        head_ = nullptr;
      }
    } else if (node->left == nullptr) {
      if (node->parent != nullptr) {
        if (node->parent->left == node) node->parent->left = node->right;
        if (node->parent->right == node) node->parent->right = node->right;
        node->right->parent = node->parent;
      } else {
        node->right->parent = nullptr;
        head_ = node->right;
      }
    } else if (node->right == nullptr) {
      if (node->parent != nullptr) {
        if (node->parent->left == node) node->parent->left = node->left;
        if (node->parent->right == node) node->parent->right = node->left;
        node->left->parent = node->parent;
      } else {
        node->left->parent = nullptr;
        head_ = node->left;
      }
    } else {
      MultiNode<Key>* temp = node->right;
      while (temp->left != nullptr) {
        temp = temp->left;
      }
      temp->left = node->left;
      temp->left->parent = temp;
      if (node->parent != nullptr) {
        if (node->parent->left == node) node->parent->left = node->right;
        if (node->parent->right == node) node->parent->right = node->right;
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

template <class Key>
void multiset<Key>::swap(multiset& other) {
  if (&other != this) {
    std::swap(head_, other.head_);
    std::swap(size_, other.size_);
  }
}

template <class Key>
void multiset<Key>::merge(multiset& other) {
  iterator it = other.begin();
  while (it != other.end()) {
    insert(it.value());
    other.erase(it);
    it = other.begin();
  }
}

template <class Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key& value) {
  size_type counter = 0;
  iterator it = find(value);
  iterator temp = it;
  while (it != end() && it.value() == temp.value()) {
    ++counter;
    ++it;
  }
  return counter;
}

template <class Key>
typename multiset<Key>::iterator multiset<Key>::find(const Key& value) {
  MultiNode<Key>* node = head_;
  while (node != nullptr && node->value != value) {
    if (node->value > value)
      node = node->left;
    else
      node = node->right;
  }
  return iterator(node);
}

template <class Key>
bool multiset<Key>::contains(const Key& value) {
  MultiNode<Key>* node = head_;
  while (node != nullptr && node->value != value) {
    if (node->value > value)
      node = node->left;
    else
      node = node->right;
  }
  return node != nullptr;
}

template <class Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key& value) {
  return std::make_pair(lower_bound(value), upper_bound(value));
}

template <class Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key& value) {
  return find(value);
}

template <class Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key& value) {
  iterator it = find(value);
  iterator temp = it;
  while (it != end() && it.value() == temp.value()) {
    ++it;
  }
  return it;
}
}  // namespace s21
