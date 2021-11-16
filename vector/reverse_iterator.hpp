#pragma once

#include <iostream>
#include <cstddef>

namespace ft
{
    template <class Iterator> class iterator_traits{
        public:
            typedef typename Iterator::difference_type   difference_type;
            typedef typename Iterator::value_type        value_type;
            typedef typename Iterator::pointer	         pointer;
            typedef typename Iterator::reference	     reference;
            typedef typename Iterator::iterator_category iterator_category;
    };

    template <class T> class iterator_traits<T*>{
        public:
        typedef  ptrdiff_t	     difference_type;
        typedef  T	             value_type;
        typedef  T*		         pointer;
        typedef  T&		         reference;
        typedef  typename std::random_access_iterator_tag iterator_category;
    };

    template <class T> class iterator_traits<const T*>{
        public:
        typedef  ptrdiff_t	                     difference_type;
        typedef  T	                             value_type;
        typedef  const  T*		                         pointer;
        typedef  const  T&		                         reference;
        typedef typename std::random_access_iterator_tag iterator_category;
    };


    template <class iterator>
    class reverse_iterator
    {
       public: 
        //for subtracting 
        typedef typename iterator_traits<iterator>::difference_type			difference_type;
        // The type of the element the iterator can point to.  
        typedef typename iterator_traits<iterator>::value_type	            value_type;
        // The type of a pointer to an element the iterator can point to.
        typedef typename iterator_traits<iterator>::pointer					pointer;
        // The type of a reference to an element the iterator can point to.
        typedef typename iterator_traits<iterator>::reference               reference;
        //the iterator category (random_access, output, input ...)
        typedef typename iterator_traits<iterator>::iterator_category	    iterator_category;

        reverse_iterator(): _it(iterator()){}

        explicit reverse_iterator(iterator it) : _it(--it) {}

        //base is next element to the iterator    -- coz its the normal iterator not the reverse 
        //so next to reverse is (++) but (--)for the normal one(iterator_type)
        iterator base() const{return _it + 1; }

        template <class Iter>
        reverse_iterator (const reverse_iterator<Iter>& rev_it){this->_it = --rev_it.base();}

        reference	operator*() const {return (*_it);}

        reverse_iterator operator+ (difference_type n) const{return(reverse_iterator(_it - n));}
        reverse_iterator operator- (difference_type n) const{return(reverse_iterator(_it + n));}

        

        reverse_iterator&	operator++() {--_it; return *this;}
        //post inc
        reverse_iterator	operator++(int) {
		    reverse_iterator tmp = *this;
				_it--;
				return (tmp);
		}
        reverse_iterator&	operator--() {++_it; return *this;}
        //post dec
        reverse_iterator	operator--(int) {
		    reverse_iterator tmp = *this;
				_it++;
				return (tmp);
		}
        
        reverse_iterator& operator+= (difference_type n){_it -= n ; return *this;}
        reverse_iterator& operator-= (difference_type n){_it += n ; return *this;}

        //must return reference to the pointer so it doesnt create another one
        pointer operator->() const{return &(*_it);}

        reference operator[] (difference_type n) const{return (base()[-n-1]);}
        

        operator reverse_iterator<const iterator>() const {
                return (reverse_iterator<const iterator>(_it));
            }
        private:
            iterator _it;

    };
    //relational operators
    template <class Iterator>
        typename reverse_iterator<Iterator>::difference_type operator- (
        const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs){return rhs.base() - lhs.base();}

        template <class Iterator>
         reverse_iterator<Iterator> operator+ (
             typename reverse_iterator<Iterator>::difference_type n,
             const reverse_iterator<Iterator>& rev_it){return (rev_it + n);}
        
        template <class Iterator>
        bool operator== (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs){return (lhs.base() == rhs.base());}
        template <class Iterator>
        bool operator!= (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs){return (lhs.base() != rhs.base());}
        template <class Iterator>
        bool operator<  (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs){return (lhs.base() > rhs.base());}
        template <class Iterator>
        bool operator>  (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs){return (lhs.base() < rhs.base());}
        template <class Iterator>
        bool operator<= (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs){return (lhs.base() >= rhs.base());}
        template <class Iterator>
        bool operator>= (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs){return (lhs.base() <= rhs.base());}
}