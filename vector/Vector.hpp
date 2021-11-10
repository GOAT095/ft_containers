#pragma once
#include "iterator.hpp"
#include <exception>
#include "reverse_iterator.hpp"
#include <iostream>
#include <memory>
#include <cstddef>
namespace ft
{
    template < class T, class Alloc = std::allocator<T> >
    class Vector
    {
        public:
            typedef Alloc allocator_type;
            // typedef T value_type;
            typedef size_t size_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type value_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type  difference_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer   pointer;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference reference;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category  iterator_category;
            typedef MyIterator<T> iterator;
            typedef MyIterator<const T> const_iterator;
            typedef reverse_iterator<const_iterator> const_reverse_iterator;
            typedef reverse_iterator<iterator> reverse_iterator;
            
            /* constructors  */
            explicit Vector (const allocator_type& alloc = allocator_type()): al(alloc), _arr(NULL),_size(0),_capacity(0)
            {
                
            }
            explicit Vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): al(alloc)
            {
                _arr = al.allocate(n);
                for (size_type i = 0; i < n; i++)
                    al.construct(&_arr[i], val);
                _size = n; _capacity = n;
            }
            template <class InputIterator> Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()):al(alloc)
            {
                _arr = allocate(last - first);
                _capacity = last - first;
                _size = _capacity;
                size_type i = 0;
                while(last != first)
                {
                    al.construct(&_arr[i], *first);
                    first++;
                    i++;
                }
            }
            Vector (const Vector& x)
            {
                _arr = nullptr;
                _size = 0;
                _capacity = 0;
                *this = x;
            }
            /*end contructors*/

            Vector &operator= (const Vector& x)
            {
                //from copy constructor
                if (_capacity != 0)
                {
                    for(size_type i = 0; i < _size; i++)
                        al.destroy(&_arr[i]);
                }
                //normal behavior
                for(size_type i = 0; i < x._size; i++)
                    al.construct(&_arr[i], x._arr[i]);
                _size = x._size;
                _capacity = x._capacity;
            }
            ~Vector(void)
            {
                for(size_type i = 0; i < _size; ++i)
			        al.destroy(&_arr[i]);
		        al.deallocate(_arr, _capacity);
            }
        iterator begin() {return (iterator(_arr));}
        const_iterator begin() const{return (iterator(_arr));}

        iterator end() {return (iterator(_arr + _size));}
        const_iterator end() const{return (iterator(_arr + _size));}

        reverse_iterator rbeging(){return(reverse_iterator(begin()));}
        const_reverse_iterator rbegin() const{return(reverse_iterator(begin()));}

        reverse_iterator rend(){return(reverse_iterator(end()));}
        const_reverse_iterator rend() const{return(reverse_iterator(end()));}
        
        
        //size
        size_type size() const{return this->_size;}
        size_type max_size() const{return al.max_size();}
        size_type capacity() const{return this->_capacity;}

        //better to start with reserve to use is for other functions
        void		reserve(size_type n) {
			if (n > _capacity) 
            {
				value_type tmp = al.allocate(n);
				for (size_type i = 0; i < _size ; i++)
                {
					al.construct(&tmp[i], _arr[i]);
					al.destroy(&_arr[i]);
				}
                //check if 0 do not deallocate
				if (_capacity != 0)
					al.deallocate(_arr, _capacity);
				_arr = tmp;
				_capacity = n;
			}
		}
        void 		resize(size_type n, value_type val = value_type()) {
			if (n <= _size)
            {
				for (size_type i = n + 1; i < _size ; i++)
					al.destroy(&_arr[i]);
				_size = n;
			} 
            else 
            {
				//reserve for new capacity
                if (n > _capacity)
					reserve(n);
				for (size_type i = _size; i < n; i++)
					al.construct(&_arr[i], val);
				_size = n;
			}
		}
        void clear()
        {
            for (size_type i = 0; i < _size ; i++)
				al.destroy(&_arr[i]);
            _size = 0;
            _capacity = 0;
        }
        bool empty() const{return (_size);}
        
        //element access
        //operator []
        reference operator[](size_type rhs) {return (*(_arr + rhs));}
        const reference operator[] (size_type rhs) const{return (*(_arr + rhs));}

        reference at (size_type n){
            if (n < 0 || n >= _size)
                throw std::string ("out of range\n");
            return(*(_arr + n));
        }
        const reference at (size_type n) const
        {
            if (n < 0 || n >= _size)
                throw std::string ("out of range\n");
            return(*(_arr + n));
        }

        reference			front() {
			return (_arr[0]);
		}
		const reference		front() const{
			return (_arr[0]);
		}

        reference 			back(){
			return (_arr[_size - 1]);
		}
		const reference		back() const{
			return (_arr[_size - 1]);
		}
        private:
            allocator_type al;
            value_type *_arr;
            size_type _size;
            size_type _capacity;

    };
};