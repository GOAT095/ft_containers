#pragma once

#include <iostream>
#include <cstddef>

namespace ft
{
    template <class Iterator> class iterator_traits{
        typedef typename Iterator::difference_type   difference_type;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::pointer	         pointer;
        typedef typename Iterator::reference	     reference;
        typedef typename Iterator::iterator_category iterator_category;
    };

    template <class T> class iterator_traits<T*>{
        typedef typename ptrdiff_t	     difference_type;
        typedef typename T	             value_type;
        typedef typename T*		         pointer;
        typedef typename T&		         reference;
        typedef typename std::random_access_iterator_tag iterator_category;
    };

    template <class T> class iterator_traits<const T*>{
        typedef typename ptrdiff_t	     difference_type;
        typedef typename T	             value_type;
        typedef const    T*		         pointer;
        typedef const    T&		         reference;
        typedef typename std::random_access_iterator_tag iterator_category;
    };

    template <class iterator>
    class reverse_iterator
    {
        //for subtracting 
        typedef          ptrdiff_t							    difference_type;
        // The type of the element the iterator can point to.  
        typedef typename iterator_traits<Iterator>::value_type	value_type;
        // The type of a pointer to an element the iterator can point to.
        typedef typename ft::iterator::pointer					pointer;
        // The type of a reference to an element the iterator can point to.
        typedef typename iterator::reference				    reference;
        //the iterator category (random_access, output, input ...)
        typedef typename iterator::iterator_category		    iterator_category;

    };
}