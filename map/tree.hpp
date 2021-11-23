#pragma once
#include "../vector/iterator.hpp"
#include "../vector/utils.hpp"
#include <exception>
#include <cstring>
#include <memory>
#include <iostream>
#define BLACK 0
#define RED 1

namespace ft{
    template <typename key, typename value>
    struct Node {
    std::pair<key, value> *data;
    Node *parent;
    Node *left;
    Node *right;
    int color;
    };
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
    class RedBlackTree {
       public:
        typedef Node *NodePtr;
        private:
          NodePtr root;
          Alloc _al;
          Compare _compare;
          // Node *TNULL;

  void initializeNULLNode(NodePtr node, NodePtr parent) {
    node->data = 0;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->color = 0;
  }

};

}