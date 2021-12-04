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
            
            NODE* previous(NODE *node)
            {
                if (node->parent && comp(node->parent->data->first, node->data->first))
                    return (node->parent);
                else if (node->left)
                    return (node->left);
            }
            NODE* next(NODE *node)
            {
                if (node->parent && comp(node->data->first, node->parent->data->first,))
                    return (node->parent);
                else if (node->right)
                    return (node->right);
            }
        };
}