#pragma once // NOLINT

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

template <typename T> class Set;

template <typename T> class Node {
public:
  T key;
  Node *left;
  Node *right;
  Node *next;
  Node *prev;
  int height;

  explicit Node(T key)
      : key(key), left(nullptr), right(nullptr), next(nullptr), prev(nullptr),
        height(1) {}
  Node()
      : left(nullptr), right(nullptr), next(nullptr), prev(nullptr), height(1) {
  }
};

template <typename T> class AVLTree {
  friend class Set<T>;

private:
  Node<T> *root;

  Node<T> *first;

  Node<T> *last;

  Node<T> *nextToLast;

  Node<T> *rightRotate(Node<T> *y);

  Node<T> *leftRotate(Node<T> *x);

  Node<T> *deleteNode(Node<T> *root, T key, bool &flag);

  Node<T> *insertNode(Node<T> *node, T key, Node<T> *next, bool &flag);

  Node<T> *nodeWithMimumValue(Node<T> *node);

  Node<T> *balance(Node<T> *node);

  void insertInList(Node<T> *prevNode, Node<T> *node);

  void deleteFromList(Node<T> *node);

  void switchNodes(Node<T> *first, Node<T> *second);

  void copyTree(Node<T> *p);

  int height(Node<T> *N);

  int getBalanceFactor(Node<T> *N);

public:
  AVLTree() : root(nullptr), nextToLast(new Node<T>) {
    first = nextToLast;
    last = nextToLast;
  }

  ~AVLTree();

  Node<T> *find(Node<T> *node, const T &key);

  Node<T> *lower_bound(Node<T> *root, Node<T> *node, const T &key);

  void insert(const T &k, bool &flag);

  void erase(const T &k, bool &flag);
};

template <typename T> void AVLTree<T>::erase(const T &k, bool &flag) {
  if (root != nullptr) {
    root = deleteNode(root, k, flag);
  }
}

template <typename T> AVLTree<T>::~AVLTree<T>() {
  while (first) {
    Node<T> *tmp = first->next;
    delete first;
    first = tmp;
  }
}

template <typename T> Node<T> *AVLTree<T>::find(Node<T> *node, const T &key) {
  if (!node) {
    return nextToLast;
  }

  if (node->key < key) {
    return find(node->right, key);
  } else if (key < node->key) {
    return find(node->left, key);
  } else {
    return node;
  }
};

template <typename T>
Node<T> *AVLTree<T>::lower_bound(Node<T> *root, Node<T> *node, const T &key) {
  if (!root) {
    return node;
  }

  if (root->key < key) {
    return lower_bound(root->right, node, key);
  } else if (key < root->key) {
    return lower_bound(root->left, root, key);
  } else {
    return root;
  }
}

template <typename T> void AVLTree<T>::insert(const T &k, bool &flag) {
  if (root == nullptr) {
    root = new Node<T>(k);
    first = root;
    last = root;
    nextToLast->prev = last;
    last->next = nextToLast;
    flag = true;
  } else {
    root = insertNode(root, k, nullptr, flag);
  }
}

template <typename T>
void AVLTree<T>::insertInList(Node<T> *prevNode, Node<T> *node) {
  Node<T> *tmp = prevNode->next;
  prevNode->next = node;
  node->next = tmp;
  node->prev = prevNode;

  if (tmp) {
    tmp->prev = node;
  }
}

template <typename T> void AVLTree<T>::deleteFromList(Node<T> *node) {
  Node<T> *prev = node->prev;
  Node<T> *next = node->next;

  if (prev == nullptr) {
    first = next;
    next->prev = nullptr;
    return;
  }

  if (next == nullptr) {
    last = prev;
    last->next = nullptr;
    return;
  }
  prev->next = next;
  next->prev = prev;
}

template <typename T> void AVLTree<T>::copyTree(Node<T> *p) {
  if (p) {
    bool tmp = true;
    root = insertNode(root, p->key, nullptr, tmp);
    copyTree(p->left);
    copyTree(p->right);
  }
}

template <typename T> Node<T> *AVLTree<T>::rightRotate(Node<T> *y) {
  Node<T> *x = y->left;
  Node<T> *T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = std::max(height(y->left), height(y->right)) + 1;
  x->height = std::max(height(x->left), height(x->right)) + 1;
  return x;
}

template <typename T> Node<T> *AVLTree<T>::leftRotate(Node<T> *x) {
  Node<T> *y = x->right;
  Node<T> *T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = std::max(height(x->left), height(x->right)) + 1;
  y->height = std::max(height(y->left), height(y->right)) + 1;
  return y;
}

template <typename T> int AVLTree<T>::height(Node<T> *N) {
  if (!N)
    return 0;
  return N->height;
}

template <typename T> int AVLTree<T>::getBalanceFactor(Node<T> *N) {
  if (N == nullptr)
    return 0;
  return height(N->left) - height(N->right);
}

template <typename T>
Node<T> *AVLTree<T>::insertNode(Node<T> *node, T key, Node<T> *next,
                                bool &flag) {
  if (node == nullptr) {
    flag = true;
    Node<T> *tmp = new Node<T>(key);
    if (next) {
      insertInList(next, tmp);
    } else {
      tmp->next = first;
      first = tmp;
    }
    return tmp;
  }

  if (key < node->key)
    node->left = insertNode(node->left, key, next, flag);
  else if (node->key < key)
    node->right = insertNode(node->right, key, node, flag);
  else
    return node;

  return balance(node);
}

template <typename T> Node<T> *AVLTree<T>::nodeWithMimumValue(Node<T> *node) {
  Node<T> *current = node;

  while (current->left != nullptr)
    current = current->left;
  return current;
}
template <typename T>
void AVLTree<T>::switchNodes(Node<T> *first, Node<T> *second) {
  if (first->next == second) {
    first->next = second->next;
    second->prev = first->prev;
    first->prev = second;
    second->next = first;

    if (first->next) {
      first->next->prev = first;
    }

    if (second->prev) {
      second->prev->next = second;
    }

    first = first->prev;
    second = first->next;

  } else {
    Node<T> *firstPrev = first->prev;
    Node<T> *firstNext = first->next;
    first->next = second->next;
    first->prev = second->prev;

    if (second->prev) {
      second->prev->next = first;
    }

    if (second->next) {
      second->next->prev = first;
    }
    second->next = firstNext;
    second->prev = firstPrev;

    if (firstPrev) {
      firstPrev->next = second;
    }

    if (firstNext) {
      firstNext->prev = second;
    }
  }

  if (this->first == second) {
    this->first = first;
  }

  if (last == second) {
    last = first;
    nextToLast->prev = first;
  }
}

template <typename T> Node<T> *AVLTree<T>::balance(Node<T> *root) {
  root->height = 1 + std::max(height(root->left), height(root->right));
  int balanceFactor = getBalanceFactor(root);

  if (balanceFactor > 1) {
    if (getBalanceFactor(root->left) >= 0) {
      return rightRotate(root);
    } else {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }
  }

  if (balanceFactor < -1) {
    if (getBalanceFactor(root->right) <= 0) {
      return leftRotate(root);
    } else {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }
  }
  return root;
}

template <typename T>
Node<T> *AVLTree<T>::deleteNode(Node<T> *root, T key, bool &flag) {
  if (!root)
    return root;

  if (key < root->key)
    root->left = deleteNode(root->left, key, flag);
  else if (root->key < key)
    root->right = deleteNode(root->right, key, flag);
  else {
    flag = true;
    if ((!root->left) || (!root->right)) {
      Node<T> *temp = root->left ? root->left : root->right;
      if (!temp) {
        temp = root;
        root = nullptr;
      } else {
        if (temp == root->left) {
          switchNodes(temp, root);
        } else {
          switchNodes(root, temp);
        }
        root->key = temp->key;
        root->height = temp->height;
        root->left = temp->left;
        root->right = temp->right;
      }
      deleteFromList(temp);
      delete temp;
    } else {
      Node<T> *temp = nodeWithMimumValue(root->right);
      root->key = temp->key;
      temp->key = key;
      switchNodes(root, temp);
      root->right = deleteNode(root->right, key, flag);
    }
  }

  if (root == nullptr)
    return root;
  return balance(root);
}
