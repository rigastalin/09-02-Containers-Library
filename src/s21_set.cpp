#include "s21_set.h"

namespace s21 {
template <class Key>
set<Key>::set(std::initializer_list<value_type> const& items) {
  auto it = items.begin();
  while (it != items.end()) {
    insert(*it);
    it++;
  }
}

template <class Key>
set<Key>::set(const set& other) : size_(other.size_) {
  Tree(other.head_);
}

template <class Key>
set<Key>::set(set&& other) : set() {
  *this = std::move(other);
}

template <class Key>
set<Key>::~set() {
  DelTree(head_);
}

template <class Key>
void set<Key>::operator=(set&& other) {
  if (&other != this) {
    size_ = other.size_;
    Tree(other.head_);
  }
}

template <class Key>
typename set<Key>::iterator set<Key>::begin() {
  SetNode<Key>* node = head_;
  while (node != nullptr && node->left != nullptr) node = node->left;
  return iterator(node);
}

template <class Key>
void set<Key>::clear() {
  DelTree(head_);
  head_ = nullptr;
  size_ = 0;
}

template <class Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type& value) {
  if (size() >= max_size()) return std::make_pair(iterator(nullptr), false);
  SetNode<Key>* node = new SetNode<Key>(value);
  std::pair<iterator, bool> pair_result = std::make_pair(iterator(node), true);
  size_ += 1;
  if (head_ == nullptr) {
    head_ = node;
  } else {
    SetNode<Key>* temp = head_;
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
        size_ -= 1;
        pair_result = std::make_pair(iterator(nullptr), false);
        delete node;
        break;
      }
    }
  }
  return pair_result;
}

template <class Key>
void set<Key>::erase(iterator pos) {
  SetNode<Key>* node = head_;
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
      SetNode<Key>* temp = node->right;
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

template <class Key>
void set<Key>::swap(set& other) {
  if (&other != this) {
    std::swap(head_, other.head_);
    std::swap(size_, other.size_);
  }
}

template <class Key>
void set<Key>::merge(set& other) {
  iterator it = other.begin();
  while (it != other.end()) {
    if (!contains(it.value())) {
      insert(it.value());
      other.erase(it);
      it = other.begin();
    } else {
      ++it;
    }
  }
}

template <class Key>
typename set<Key>::iterator set<Key>::find(const Key& value) {
  SetNode<Key>* node = head_;
  while (node != nullptr && node->value != value) {
    if (node->value > value)
      node = node->left;
    else
      node = node->right;
  }
  return iterator(node);
}

template <class Key>
bool set<Key>::contains(const Key& value) {
  SetNode<Key>* node = head_;
  while (node != nullptr && node->value != value) {
    if (node->value > value)
      node = node->left;
    else
      node = node->right;
  }
  return node != nullptr;
}
}  //  namespace s21
