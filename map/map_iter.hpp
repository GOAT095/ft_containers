#pragma once
#include "../vector/iterator.hpp"

namespace ft{
    template <class NODE, class T, class comp>
        class map_iter : public ft::MyIterator<std::bidirectional_iterator_tag, T>
        {
            private:
                NODE *_p;
            
            public :
                // typedef typename ft::MyIterator<std::bidirectional_iterator_tag, T>::value_type                value_type;
                // typedef typename ft::MyIterator<std::bidirectional_iterator_tag, T>::difference_type           difference_type;
                // typedef typename ft::MyIterator<std::bidirectional_iterator_tag, T>::pointer                   pointer;
                // typedef typename ft::MyIterator<std::bidirectional_iterator_tag, T>::reference                 reference;
                // typedef typename ft::MyIterator<std::bidirectional_iterator_tag, T>::iterator_category         iterator_category;
            
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
            *T operator->() const{ return (_p->data);}
            &T operator*() const{ return (*_p->data);}
        };
}