#pragma once
#include "../vector/iterator.hpp"

namespace ft{
    template <class NODE, class T, class comp>
        class map_iter : public ft::iterator<std::bidirectional_iterator_tag, T>
        {
            private:
                NODE *_p;
                NODE *_root;
                NODE * minValueNode(NODE* node)
                {
                    NODE* current = node;
                
                    /* loop down to find the rightmost leaf */
                    while (current && current->left != NULL)
                        current = current->left;
                
                    return current;
                }
                NODE * maxValueNode(NODE* node)
                {
                    NODE* current = node;
                
                    /* loop down to find the leftmost leaf */
                    while (current && current->right != NULL)
                        current = current->right;
                
                    return current;
                }
                NODE *min;
                NODE *max;
            
            public :
            
            map_iter(){
                _p = NULL;
                _root = NULL;
            }
             map_iter(NODE *node, NODE *root){
                _p = node;
                _root = root;
            }
            map_iter(const map_iter& copy)
            {
                *this = copy;
            }
            map_iter&   operator=(const map_iter& rhs)
            {
                _p = rhs._p;
                _root = rhs._root;
                return (*this);
            }
            ~map_iter(){}
            T* operator->() const{ return (_p->data);}
            T& operator*() const{ return (*_p->data);}
            
            map_iter& operator--()
            {
                NODE *n = _p;
                NODE *min = minValueNode(_root);
                NODE *max = maxValueNode(_root);
                if (_p == NULL)
                { _p = max ;  return (*this);}
                if (_p == min)
                {    _p = NULL; return *this;}
                // if it has left, left it is :)
                if (n->left != NULL)
                    _p = minValueNode(n->left);
            
                // if doesnt have right you need to get it from parents
                else if (n->right == NULL)
                {
                    NODE* p = n->parent;
                    while (p != NULL && n == p->left)
                    {
                        n = p;
                        p = p->parent;
                        
                    }
                    _p = p;
                }
                
                return (*this);
            }
            NODE *getNode() const
            {
                return _p;
            }
            map_iter operator++(int)
            {
                map_iter tmp(*this);
                this->operator++();
                return (tmp);
            }
            
            map_iter& operator++()
            {
                NODE *n = _p;
                NODE *max = maxValueNode(_root);
                // if (_p == NULL)
                // { _p = max ;  return (*this);}
                if (_p == max)
                {    _p = NULL; return *this;}
                // if it has right right it is :)
                if (n->right != NULL)
                    _p = minValueNode(n->right);

                // if doesnt have right you need to get it from parents
                
                else if (n->right == NULL)
                {   
                    NODE* p = n->parent;
                    while (p != NULL && n == p->right)
                    {
                        n = p;
                        p = p->parent;
                        
                    }
                    _p = p;
                }

                return (*this);
            }
            map_iter operator--(int)
            {
                map_iter tmp(*this);
                this->operator--();
                return (tmp);
            }

            operator map_iter<NODE, T,comp>() const{return map_iter<NODE, T,comp>(_p);}
            friend bool	operator==(map_iter const& lhs, map_iter const& rhs) { return (lhs._p == rhs._p); }
            friend bool	operator!=(map_iter const& lhs, map_iter const& rhs) { return (lhs._p != rhs._p); }
        };
}