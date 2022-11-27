#pragma once // NOLINT

#include "avltree.h"
#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <vector>

template <typename T> class Set {
private:
  size_t len;

  AVLTree<T> *tree;

public:
  class iterator {
  public:
    iterator() : ptr(nullptr){};
    iterator(const iterator &it) : ptr(it.ptr) {}
    explicit iterator(Node<T> *node) : ptr(node) {}

    iterator &operator=(const iterator &it) {
      if (this != &it) {
        ptr = it.ptr;
      }
      return *this;
    }

    bool operator==(const iterator &it) const { return ptr == it.ptr; }
    bool operator!=(const iterator &it) const { return ptr != it.ptr; }
    bool operator<(const iterator &it) const { return **this < *it; }
    bool operator>(const iterator &it) const { return **this > *it; }
    bool operator<=(const iterator &it) const { return **this <= *it; }

    bool operator>=(const iterator &it) const { return **this >= *it; }
    const T &operator*() const { return ptr->key; }
    T const *operator->() const { return &(ptr->key); };
    iterator operator++() {
      if (ptr->next == nullptr) {
        return *this;
      }
      ptr = ptr->next;
      return *this;
    }
    iterator operator--() {
      ptr = ptr->prev;
      return *this;
    }

    iterator operator++(int) {
      iterator old(*this);
      ++(*this);
      return old;
    }
    iterator operator--(int) {
      iterator old(*this);
      --(*this);
      return old;
    }

  private:
    Node<T> *ptr;
  };

  class const_iterator {
  public:
    const_iterator() : ptr(nullptr){};
    const_iterator(const const_iterator &it) : ptr(it.ptr) {}
    explicit const_iterator(Node<T> *node) : ptr(node) {}

    const_iterator &operator=(const iterator &it) {
      if (this != &it) {
        ptr = it.ptr;
      }
      return *this;
    }

    bool operator==(const const_iterator &it) const { return ptr == it.ptr; }
    bool operator!=(const const_iterator &it) const { return ptr != it.ptr; }
    bool operator<(const const_iterator &it) const { return **this < *it; }
    bool operator>(const const_iterator &it) const { return **this > *it; }
    bool operator<=(const const_iterator &it) const { return **this <= *it; }
    bool operator>=(const const_iterator &it) const { return **this >= *it; }
    const T &operator*() const { return ptr->key; }
    T const *operator->() const { return &(ptr->key); };

    const_iterator operator++() {
      if (ptr->next == nullptr) {
        return *this;
      }
      ptr = ptr->next;
      return *this;
    }

    const_iterator operator--() {
      ptr = ptr->prev;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator old(*this);
      ++(*this);
      return old;
    }

    const_iterator operator--(int) {
      const_iterator old(*this);
      --(*this);
      return old;
    }

  private:
    Node<T> *ptr;
  };

  Set();
  Set(std::initializer_list<T>);
  Set(const Set<T> &other);
  template <class InputIt> Set(InputIt first, InputIt lasts);
  Set<T> &operator=(const Set<T> &other);
  ~Set();

  void insert(const T &key);
  void erase(const T &key);

  iterator begin() const { return iterator(tree->first); }
  iterator end() const { return iterator(tree->nextToLast); }

  const_iterator cbegin() const { return const_iterator(tree->first); }
  const_iterator cend() const { return const_iterator(tree->nextToLast); }

  iterator find(const T &key) const {
    return iterator(tree->find(tree->root, key));
  };

  iterator lower_bound(const T &key) const {
    return iterator(tree->lower_bound(tree->root, tree->nextToLast, key));
  };

  size_t size() const;
  bool empty() const;
};

template <typename T>
template <class InputIt>
Set<T>::Set(InputIt first, InputIt last) : len(0), tree(new AVLTree<T>) {
  for (; first != last; ++first) {
    bool flag = false;
    tree->insert(*first, flag);
    len += flag ? 1 : 0;
  }
}

template <typename T> Set<T>::~Set<T>() { delete tree; }

template <typename T> Set<T> &Set<T>::operator=(const Set<T> &other) {
  if (this != &other) {
    delete tree;
    len = 0;
    tree = new AVLTree<T>;
    for (Set<T>::iterator i = other.begin(); i != other.end(); i++) {
      insert(*i);
    }
  }

  return *this;
}

template <typename T>
Set<T>::Set(const Set<T> &other) : len(0), tree(new AVLTree<T>) {
  for (Set<T>::iterator i = other.begin(); i != other.end(); ++i) {
    insert(*i);
  }
}

template <typename T> Set<T>::Set() : len(0), tree(new AVLTree<T>) {}

template <typename T>
Set<T>::Set(std::initializer_list<T> list) : len(0), tree(new AVLTree<T>) {
  auto *item = list.begin();

  for (; item != list.end(); ++item) {
    bool flag = false;
    tree->insert(*item, flag);
    if (flag) {
      ++len;
    }
  }
}

template <typename T> size_t Set<T>::size() const { return len; }

template <typename T> bool Set<T>::empty() const { return len == 0; }

template <typename T> void Set<T>::insert(const T &key) {
  bool flag = false;
  tree->insert(key, flag);

  if (flag) {
    ++len;
  }
}

template <typename T> void Set<T>::erase(const T &key) {
  bool flag = false;
  tree->erase(key, flag);

  if (flag) {
    --len;
  }
}
