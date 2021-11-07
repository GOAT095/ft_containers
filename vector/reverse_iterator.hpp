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
        typedef typename ptrdiff_t	                     difference_type;
        typedef typename T	                             value_type;
        typedef const    T*		                         pointer;
        typedef const    T&		                         reference;
        typedef typename std::random_access_iterator_tag iterator_category;
    };

    template <class iterator>
    class reverse_iterator
    {
       public: 
        //for subtracting 
        typedef typename iterator_traits<Iterator>::difference_type			difference_type;
        // The type of the element the iterator can point to.  
        typedef typename iterator_traits<Iterator>::value_type	            value_type;
        // The type of a pointer to an element the iterator can point to.
        typedef typename iterator_traits<Iterator>::pointer					pointer;
        // The type of a reference to an element the iterator can point to.
        typedef typename iterator_traits<Iterator>::reference               reference;
        //the iterator category (random_access, output, input ...)
        typedef typename iterator_traits<Iterator>::iterator_category	    iterator_category;

        typedef typename iterator::iterator_type                iterator_type;

        reverse_iterator(): _it(iterator_type())){}

        explicit reverse_iterator(iterator_type &it) : _it(it) {}

        //base is next element to the iterator    
        iterator_type base() const{iterator_type tmp; tmp = this->_it; return ++tmp;}
        template <class Iter>
        reverse_iterator (const reverse_iterator<Iter>& rev_it){this->_it = rev_it.base();}

        reference	operator*() const {return (*_it);}

        reverse_iterator operator+ (difference_type n) const{return(reverse_iterator(_it - n);}
        reverse_iterator operator- (difference_type n) const{return(reverse_iterator(_it + n);}

        reverse_iterator&	operator++() {--_it; return *this;}
        //post inc
        reverse_iterator	operator++(int) {
		    reverse_iterator tmp = *this;
				_it--;
				return (tmp);
		}
        reverse_iterator&	operator--() {++_it; return *this;}
        //post inc
        reverse_iterator	operator++(int) {
		    reverse_iterator tmp = *this;
				_it++;
				return (tmp);
		}
        
        reverse_iterator& operator+= (difference_type n){_it -= n ; return *this;}
        reverse_iterator& operator-= (difference_type n){_it += n ; return *this;}

        //must return reference to the pointer so it doesnt create another one
        pointer operator->() const{return &(*_it);}

        reference operator[] (difference_type n) const{return (_it[n]);}

        //relational operators
        template <class Iterator>
        friend bool operator== (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs){return (lhs._it == rhs._it);}
        friend bool operator!= (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs){return (lhs._it != rhs._it);}
        template <class Iterator>
        friend bool operator<  (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs){return (lhs._it < rhs._it);}
        template <class Iterator>
        friend bool operator>  (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs){return (lhs._it > rhs._it);}
        template <class Iterator>
        friend bool operator<= (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs){return (lhs._it <= rhs._it);}
        template <class Iterator>
        friend bool operator<= (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs){return (lhs._it >= rhs._it);}
        
        
        template <class Iterator>
        friend typename reverse_iterator<Iterator>::difference_type operator- (
        const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs){return (lhs.base() - rhs.base());}

        template <class Iterator>
        reverse_iterator<Iterator> operator+ (
             typename reverse_iterator<Iterator>::difference_type n,
             const reverse_iterator<Iterator>& rev_it){return (rev_it + n;)}
        private:
            iterator_type _it;

    };
}