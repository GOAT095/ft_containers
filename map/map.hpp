#pragma once

#include <exception>
#include <cstring>
#include <memory>
#include <iostream>

namespace ft{
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
    class map
    {
        typedef T mapped_type;
        typedef key;
        typedef Compare key_compare;

    };

}