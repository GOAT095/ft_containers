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
    // template <typename T>
    // struct Node {
    // T *data;
    // Node *parent;
    // Node *left;
    // Node *right;
    // };
    template < class T, class Compare, class Alloc = std::allocator<T> >
    class AVL {
        
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef Compare compare;
        private:
          AVL *root;
          Alloc _al;
          Compare _compare;
          T *data;
          AVL *parent;
          AVL *left;
          AVL *right;
          // Node *TNULL;
        public:

        explicit AVL(value_type val)
        {
          data = _al.allocate(1);
          _al.construct(data, val);
          root = parent = left = right =NULL;
        }
        

};

}