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
        typedef Key key_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef	size_t                             size_type;
        typedef	size_t                             difference_type;
        typedef ft::Node<
        //constractors and stuff
        //empty
        explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
        {
            _size = 0;
            al = alloc;
            kc = comp;
            _capacity = 0;
        }
        template <class InputIterator>
        map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
        {
            
            //need insert with iters
            kc = comp;
            al = alloc;
            _size = 0;
        }
        map (const map& x)
        {
            _size = 0;
            *this = x;
        }
        ~map(){
            clear();
        }
        private:
        size_t  _size;
        size_t  _capacity;
        Alloc   al;
        key_compare kc;
    };

}