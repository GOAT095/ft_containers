#pragma once

#include <iostream>
#include <memory>

namespace ft
{
    template <typname T>
    T   *allocate_memory_vector(std::acllocator<T> allocat, size_t n)
    {
        try{
            T *array;
            array = allocat.allocate(n)
        }
        catch(std::bad_alloc &e)
        {
            std::cout << e.what() << "\n";
        }
        return (array);

    }


}