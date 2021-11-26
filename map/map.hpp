#pragma once

#include <exception>
#include <cstring>
#include <memory>
#include <iostream>
#include "map-utils.hpp"

namespace ft{
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
    class map
    {
        typedef T mapped_type;
        typedef key;
        typedef Compare key_compare;
    };

}