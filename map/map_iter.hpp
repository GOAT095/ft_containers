#pragma once
#include "../vector/iterator.hpp"
template <class NODE, class T, class comp>
    class map_iter : public ft_iterator<std::bidirectional_iterator_tag, T>
    {
        
        public :
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::value_type                value_type;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type           difference_type;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::pointer                   pointer;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::reference                 reference;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category         iterator_category;
        
    };