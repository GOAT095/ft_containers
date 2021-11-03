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
            typedef T value_type;
            typedef size_t size_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type value_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type  difference_type;
             typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer   pointer;
             typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference reference;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category  iterator_category;
            typedef Iterator<T> iterator;

            /* constructors  */
            explicit Vector (const allocator_type& alloc = allocator_type()): al(alloc), arr(NULL),size(0),capacity(0)
            {
                
            }
            explicit Vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): al(alloc)
            {
                arr = al.allocate(n);
                for (size_type i = 0; i < n; i++)
                    al.construct(arr[i], val);
                size = n; capacity = n;
            }
            template <class InputIterator> Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()):al(alloc)
            {
                arr = allocate(last - first);
                capacity = last - first;
                size = capacity;
                size_type i = 0;
                while(last != first)
                {
                    al.construct(arr[i], *first);
                    first++;
                    i++;
                }
            }
            Vector (const Vector& x)
            {
                arr = nullptr;
                size = 0;
                capacity = 0;
                *this = x;
            }
            /*end contructors*/

            Vector &operator= (const Vector& x)
            {
                //from copy constructor
                if (capacity != 0)
                {
                    for(size_type i = 0; i < size; i++)
                        al.destroy(&arr[i]);
                }
                //normal behavior
                for(size_type i = 0; i < x.size; i++)
                    al.construct(arr[i], x.arr[i]);
                size = x.size;
                capacity = x.capacity;
            }
            ~Vector(void)
            {
                for(size_type i = 0; i < size; ++i)
			        al.destroy(&arr[i]);
		        al.deallocate(arr, capacity);
            }
            iterator begin()
            {
                return (iterator(&arr[0]));
            }

        private:
            allocator_type al;
            value_type *arr;
            size_type size;
            size_type capacity;

    };
};