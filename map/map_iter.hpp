#pragma once
#include "../vector/iterator.hpp"

namespace ft{
    template <class NODE, class T, class comp>
        class map_iter : public ft::iterator<std::bidirectional_iterator_tag, T>
        {
            private:
                NODE *_p;
                NODE *_root;
                NODE *_end;
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
                NODE * minValueNode(NODE* node) const
                {
                    NODE* current = node;
                
                    /* loop down to find the rightmost leaf */
                    while (current && current->left != NULL)
                        current = current->left;
                
                    return current;
                }
                NODE * maxValueNode(NODE* node) const
                {
                    NODE* current = node;
                
                    /* loop down to find the leftmost leaf */
                    while (current && current->right != NULL)
                        current = current->right;
                
                    return current;
                }
                // NODE *min;
                // NODE *max;
            
            public :
            
            map_iter(){
                _p = NULL;
                _end = NULL;
            }
            map_iter(NODE *node, NODE *root){
                _p = node;
                _root = root;
                _end = NULL;
            }
             map_iter(NODE *node, NODE *root, NODE* end){
                _p = node;
                _root = root;
                _end = end;
            }
            map_iter(const map_iter& copy)
            {
                *this = copy;
            }
            map_iter&   operator=(const map_iter& rhs)
            {
                _p = rhs._p;
                _root = rhs._root;
                _end = rhs._end;
                return (*this);
            }
            ~map_iter(){}
            T* operator->() const{ return (_p->data);}
            T& operator*() const{ return (*_p->data);}
            
            map_iter& operator--()
            {
                NODE *n = _p;
                NODE *min = minValueNode(_root);
                // NODE *max = maxValueNode(_root);
                //if points to end give it max value thats on end
                if (_p == NULL && _end)
                {
                    _p = _end;
                    _end = NULL;
                    return (*this);
                }
                if (_p == min)
                {return *this;}
                // if it has left, left it is :)
                
                if (n->left != NULL)
                    _p = minValueNode(n->left);
            
                // if doesnt have right you need to get it from parents
                else if (n->left == NULL)
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
            
            
            map_iter& operator++()
            {
                NODE *n = _p;
                NODE *max = maxValueNode(_root);
                //if last element should point to end
                if (_p == max)
                {    _p = NULL;
                    _end = _p;
                    return *this;
                }
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
            map_iter operator++(int)
            {
                map_iter tmp(*this);
                this->operator++();
                return (tmp);
            }
            map_iter operator--(int)
            {
                map_iter tmp(*this);
                this->operator--();
                return (tmp);
            }

            operator map_iter<NODE, const T,comp>() const{return map_iter<NODE, const T,comp>(_p, _root, _end);}
            friend bool	operator==(map_iter const& lhs, map_iter const& rhs) { return (lhs._p == rhs._p); }
            friend bool	operator!=(map_iter const& lhs, map_iter const& rhs) { return (lhs._p != rhs._p); }
        };
}