#pragma once

#include <iostream>
#include <cstddef>

namespace ft
{
    template <class iterator>
    class reverse_iterator
    {
        //for subtracting 
        typedef ptrdiff_t									difference_type;
        // The type of the element the iterator can point to.  
        typedef typename Iterator::value_type				value_type;
        // The type of a pointer to an element the iterator can point to.
        typedef typename Iterator::pointer					pointer;
        // The type of a reference to an element the iterator can point to.
        typedef typename Iterator::reference				reference;
        //the iterator category (random_access, output, input ...)
        typedef typename Iterator::iterator_category		iterator_category;

    };
}