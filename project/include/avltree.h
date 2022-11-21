#pragma once // NOLINT

#include <algorithm>
#include <iostream>

template <typename T> class Set;

template <typename T> class Node {
public:
  T key;
  Node *left;
  Node *right;
  int height;

  explicit Node(T key) : key(key), left(nullptr), right(nullptr), height(1) {}
};

template <typename T> class AVLTree {
  friend class Set<T>;

private:
  Node<T> *rightRotate(Node<T> *y);
  void deleteTree(Node<T> *p);
  Node<T> *leftRotate(Node<T> *x);

  void CopyTree(Node<T> *p);

  int height(Node<T> *N);

  int getBalanceFactor(Node<T> *N);

  Node<T> *insertNode(Node<T> *node, int key, bool &flag);

  Node<T> *nodeWithMimumValue(Node<T> *node);

  Node<T> *deleteNode(Node<T> *root, int key, bool &flag);

public:
  Node<T> *root;

  AVLTree() : root(nullptr) {}
  ~AVLTree();

  explicit AVLTree(int a) : root(new Node<T>(a)) {}
  explicit AVLTree(const AVLTree<T> &other);
  void printTree(Node<T> *root, std::string indent, bool last);

  void insert(T k, bool &flag);
  void erase(T k, bool &flag);
};

template <typename T> void AVLTree<T>::erase(T k, bool &flag) {
  if (root != nullptr) {
    root = deleteNode(root, k, flag);
  }
}

template <typename T> void AVLTree<T>::deleteTree(Node<T> *p) {
  if (p) {
    deleteTree(p->left);
    deleteTree(p->right);
    delete p;
  }
}

template <typename T> AVLTree<T>::~AVLTree<T>() { deleteTree(root); }

template <typename T> void AVLTree<T>::insert(T k, bool &flag) {
  if (root == nullptr) {
    root = new Node<T>(k);
    flag = true;
  } else {
    root = insertNode(root, k, flag);
  }
}
template <typename T>
void AVLTree<T>::printTree(Node<T> *root, std::string indent, bool last) {
  if (root != nullptr) {
    std::cout << indent;
    if (last) {
      std::cout << "R----";
      indent += "   ";
    } else {
      std::cout << "L----";
      indent += "|  ";
    }
    std::cout << root->key << std::endl;
    printTree(root->left, indent, false);
    printTree(root->right, indent, true);
  }
}

template <typename T> void AVLTree<T>::CopyTree(Node<T> *p) {
  if (p) {
    bool tmp = true;
    root = insertNode(root, p->key, tmp);
    CopyTree(p->left);
    CopyTree(p->right);
  }
}

template <typename T>
AVLTree<T>::AVLTree(const AVLTree<T> &other)
    : root(new Node<T>(other.root->key)) {
  CopyTree(other.root->left);
  CopyTree(other.root->right);
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
Node<T> *AVLTree<T>::insertNode(Node<T> *node, int key, bool &flag) {
  if (node == nullptr) {
    flag = true;
    return new Node<T>(key);
  }
  if (key < node->key)
    node->left = insertNode(node->left, key, flag);
  else if (key > node->key)
    node->right = insertNode(node->right, key, flag);
  else
    return node;

  node->height = 1 + std::max(height(node->left), height(node->right));
  int balanceFactor = getBalanceFactor(node);
  if (balanceFactor > 1) {
    if (key < node->left->key) {
      return rightRotate(node);
    } else if (key > node->left->key) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }

  if (balanceFactor < -1) {
    if (key > node->right->key) {
      return leftRotate(node);
    } else if (key < node->right->key) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }
  return node;
}

template <typename T> Node<T> *AVLTree<T>::nodeWithMimumValue(Node<T> *node) {
  Node<T> *current = node;
  while (current->left != nullptr)
    current = current->left;
  return current;
}

template <typename T>
Node<T> *AVLTree<T>::deleteNode(Node<T> *root, int key, bool &flag) {
  if (root == nullptr)
    return root;
  if (key < root->key)
    root->left = deleteNode(root->left, key, flag);
  else if (key > root->key)
    root->right = deleteNode(root->right, key, flag);
  else {
    flag = true;
    if ((root->left == nullptr) || (root->right == nullptr)) {
      Node<T> *temp = root->left ? root->left : root->right;
      if (temp == nullptr) {
        temp = root;
        root = nullptr;
      } else
        *root = *temp;
      free(temp);
    } else {
      Node<T> *temp = nodeWithMimumValue(root->right);
      root->key = temp->key;
      root->right = deleteNode(root->right, temp->key, flag);
    }
  }

  if (root == nullptr)
    return root;

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
