#pragma once

#include <iostream>
#include <memory>

namespace ft
{
    template <typename T>
    T   *allocate_memory_vector(std::allocator<T> alloc, size_t n)
    {   
        T *array;
        try{
            
            array = alloc.allocate(n);
        }
        catch(std::bad_alloc &e)
        {
            std::cerr << e.what() << "\n";
        }
        return (array);
    }
    template <typename T, std::allocator<T> alloc>
    void deallocate_memory( T* p, std::size_t n)
    {
        alloc.deallocate(p, n);
    }
}