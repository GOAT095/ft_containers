#pragma once

#include <iostream>
#include <memory>

namespace ft
{
    
    template < class T, class Alloc = allocator<T>
    class Vector
    {
        public:
            typedef Alloc allocator_type;
            typedef T value_type;

            /* constructors  */
            explicit vector (const allocator_type& alloc = allocator_type()): al(alloc), arr(NULL),size(0),capacity(0)
            {
                
            }
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): al(alloc)
            {
                //need to use construct so it doesnt use = op
                arr = al.allocate(n);
                for (int i = 0; i < n; i++)
                    al.construct(arr[i], val);
                size = n; capacity = n;
            }
            template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()):al(alloc)
            {
                arr = allocate(last - first);
                capacity = last - first;
                size = capacity;
                int i = 0;
                while(last != first)
                {
                    al.construct(arr[i], *first);
                    first++;
                    i++;
                }
            }
            vector (const vector& x)
            {
                *this = x;
            }
            /*end contructors*/

            Vector &operator= (const vector& x)
            {
                
            }
        private:
            allocator_type al;
            value_type *arr;
            size_t size;
            size_t capacity;

    }
}