#pragma once
#include "../vector/iterator.hpp"

namespace ft{
    template <class NODE, class T, class comp>
        class map_iter : public ft::iterator<std::bidirectional_iterator_tag, T>
        {
            private:
                NODE *_p;
            
            public :
            
            map_iter(){
                _p = NULL;
            }
            map_iter(const NODE& node){
                _p = node;
            }
            map_iter(const map_iter& copy)
            {
                *this = copy;
            }
            map_iter&   operator=(const map_iter& rhs)
            {
                _p = rhs._p;
                return (*this);
            }
            ~map_iter(){}
            T* operator->() const{ return (_p->data);}
            T& operator*() const{ return (*_p->data);}
            
            NODE* previous(NODE *n)
            {
                 // if it has left, left it is :)
                if (n->left != NULL)
                    return minValue(n->left);
            
                // if doesnt have right you need to get it from parents
                NODE* p = n->parent;
                while (p != NULL && n == p->left)
                {
                    n = p;
                    p = p->parent;
                }
                return p;
            }
            
            NODE* next(NODE *n)
            {
                // if it has right right it is :)
                if (n->right != NULL)
                    return minValue(n->right);
            
                // if doesnt have right you need to get it from parents
                NODE* p = n->parent;
                while (p != NULL && n == p->right)
                {
                    n = p;
                    p = p->parent;
                }
                return p;
            }
        };
}