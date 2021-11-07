#pragma once
#include "iterator.hpp"
#include <iostream>
#include <memory>
#include <cstddef>
namespace ft
{
    template < class T, class Alloc = std::allocator<T> >
    class Vector
    {
        public:
            typedef Alloc allocator_type;
            // typedef T value_type;
            typedef size_t size_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type value_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type  difference_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer   pointer;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference reference;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category  iterator_category;
            typedef MyIterator<T> iterator;

            /* constructors  */
            explicit Vector (const allocator_type& alloc = allocator_type()): al(alloc), _arr(NULL),_size(0),_capacity(0)
            {
                
            }
            explicit Vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): al(alloc)
            {
                _arr = al.allocate(n);
                for (size_type i = 0; i < n; i++)
                    al.construct(&_arr[i], val);
                _size = n; _capacity = n;
            }
            template <class InputIterator> Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()):al(alloc)
            {
                _arr = allocate(last - first);
                _capacity = last - first;
                _size = _capacity;
                size_type i = 0;
                while(last != first)
                {
                    al.construct(&_arr[i], *first);
                    first++;
                    i++;
                }
            }
            Vector (const Vector& x)
            {
                _arr = nullptr;
                _size = 0;
                _capacity = 0;
                *this = x;
            }
            /*end contructors*/

            Vector &operator= (const Vector& x)
            {
                //from copy constructor
                if (_capacity != 0)
                {
                    for(size_type i = 0; i < _size; i++)
                        al.destroy(&_arr[i]);
                }
                //normal behavior
                for(size_type i = 0; i < x._size; i++)
                    al.construct(&_arr[i], x._arr[i]);
                _size = x._size;
                _capacity = x._capacity;
            }
            ~Vector(void)
            {
                for(size_type i = 0; i < _size; ++i)
			        al.destroy(&_arr[i]);
		        al.deallocate(_arr, _capacity);
            }
        iterator begin() {return (iterator(_arr));}
        iterator end() {return (iterator(_arr + _size));}
        
        //operator []
        reference operator[](size_type rhs) {return (*(_arr + rhs));}
        const reference operator[] (size_type rhs) const{return (*(_arr + rhs));}
        
        //size
        size_type size() const{return this->_size;}
        size_type max_size() const{return al.max_size();}
        size_type capacity() const{return this->_capacity;};

        private:
            allocator_type al;
            value_type *_arr;
            size_type _size;
            size_type _capacity;

    };
};