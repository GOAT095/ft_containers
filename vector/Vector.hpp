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


            explicit vector (const allocator_type& alloc = allocator_type()): al(alloc), arr(NULL),size(0),capacity(0)
            {
                
            }
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
            {
                
            }
            template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
            {

            }
            vector (const vector& x)
            {

            }

        private:
            allocator_type al;
            value_type *arr;
            size_t size;
            size_t capacity;

    }
}