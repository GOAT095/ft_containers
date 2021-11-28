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
        Node &operator=(const Node &rhs)
        {
            root = rhs.root;
            left = rhs.left;
            right = rhs.right;
            parent = rhs.parent;
            if (value)
                al.deallocate(value, 1);
            value = al.allocate(1);
            al.construct(value, *(rhs.value));
            height = rhs.height;
            return (*this);
        }
        ~Node(){}


        Node*   rotateRight(Node* y)
        {
            Node* x = y->left;
            Node* T2 = x->right;

            // do rotate
            if (x->right)
                x->right->parent = y;
            x->right = y;
            y->left = T2;
            // update parent
            x->parent = y->parent;
            y->parent = x;
            // recalculate x and y heights
            x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
            y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

            // return new tree root
            return (x);
        }

        Node*   rotateLeft(Node* x)
        {
            Node *y = x->right;
            // if (!y)
                // exit(0);
            Node *T2 = y->left;

            // Perform rotation
            if (y->left)
                y->left->parent = x;
            y->left = x;
            x->right = T2;
            // update parents
            y->parent = x->parent;
            x->parent = y;


            // Update heights
            x->height = std::max(getHeight(x->left),
                            getHeight(x->right)) + 1;
            y->height = std::max(getHeight(y->left),
                            getHeight(y->right)) + 1;

            // Return new root
            return y;
        }
};