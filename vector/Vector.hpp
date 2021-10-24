#pragma once

#include <iostream>
#include <memory>
#include <STL>
#include 
namespace ft
{
    
    template < class T, class Alloc = std::allocator<T> >
    class Vector
    {
        public:
            typedef Alloc allocator_type;
            typedef T value_type;
            typedef size_t size_type;
            typedef iterator std::random_access_iterator_tag<T>;

            /* constructors  */
            explicit vector (const allocator_type& alloc = allocator_type()): al(alloc), arr(NULL),size(0),capacity(0)
            {
                
            }
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): al(alloc)
            {
                //need to use construct so it doesnt use = op
                arr = al.allocate(n);
                for (size_type i = 0; i < n; i++)
                    al.construct(arr[i], val);
                size = n; capacity = n;
            }
            template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()):al(alloc)
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
            vector (const vector& x)
            {
                arr = nullptr;
                size = 0;
                capacity = 0;
                *this = x;
            }
            /*end contructors*/

            Vector &operator= (const vector& x)
            {
                //from copy constructor
                if (capacity != 0)
                {
                    for(size_type i = 0; i < size; i++)
                        al.destroy(*arr[i]);
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
        private:
            allocator_type al;
            value_type *arr;
            size_type size;
            size_type capacity;

    };
};