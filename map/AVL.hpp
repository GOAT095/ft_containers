#pragma once
#include "map-utils.hpp"

template<typename T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
class Node
{
    public:
        typedef T value_type;
        // typedef Node node;

        value_type   *value;
        Node  *right;
        Node  *left;
        Node  *parent;
        Node  *root;
        int   height;
        Alloc al;
        Compare key_compare;

        Node()
        {
            right = left = root = parent = NULL;
            value = NULL;
            height = 0;
        }
        Node(const value_type& val)
        {
            value = al.allocate(1);
            al.construct(value, val);
            right = left = NULL;
            height = 1;
            root = this;
            parent = NULL;
        }
        Node(Node<value_type, Compare, Alloc> *root)
        {
            right = left = parent = NULL;
            height = root->height;
            this->root = root;
        }

};