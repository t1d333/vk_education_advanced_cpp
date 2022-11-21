#pragma once // NOLINT

#include "avltree.h"
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <vector>

template <typename T> class Set {
private:
  AVLTree<T> *tree;
  size_t len;

public:
  void print() { tree->printTree(tree->root, "", true); }
  Set();
  Set(std::initializer_list<T>);
  Set(const Set<T> &other);
  template <class InputIt> Set(InputIt first, InputIt lasts);
  Set<T> &operator=(const Set<T> &other);
  ~Set();

  void insert(T key);
  void erase(T key);

  size_t size() const;
  bool empty() const;
  void getData(std::vector<T> &buf);
};

template <typename T>
template <class InputIt>
Set<T>::Set(InputIt first, InputIt last) {
  for (; first != last; ++first) {
    bool flag = false;
    tree->insert(*first, flag);
    len += flag ? 1 : 0;
  }
}

template <typename T> void Set<T>::getData(std::vector<T> &buf) {
  tree->getData(tree->root, buf);
}

template <typename T> Set<T>::~Set<T>() { delete tree; }

template <typename T> Set<T> &Set<T>::operator=(const Set<T> &other) {
  if (this != &other) {
    delete tree;
    len = other.len;
    tree = new AVLTree<T>(*other.tree);
  }
  return *this;
}

template <typename T> Set<T>::Set(const Set<T> &other) : len(other.len) {
  tree = new AVLTree<T>(*other.tree);
}

template <typename T> Set<T>::Set() : tree(new AVLTree<T>), len(0) {}

template <typename T>
Set<T>::Set(std::initializer_list<T> list) : tree(new AVLTree<T>), len(0) {
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

template <typename T> void Set<T>::insert(T key) {
  bool flag = false;
  tree->insert(key, flag);
  if (flag) {
    ++len;
  }
}

template <typename T> void Set<T>::erase(T key) {
  bool flag = false;
  tree->erase(key, flag);
  if (flag) {
    --len;
  }
}
