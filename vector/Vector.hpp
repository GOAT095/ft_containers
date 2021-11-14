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
                _arr = al.allocate(last - first);
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
				value_type *tmp = al.allocate(n);
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
        //returns true if empty
        bool empty() const{return (_size==0);}
        
        //element access
        //operator []
        reference operator[](size_type rhs) {return _arr[rhs];}
        const reference operator[] (size_type rhs) const{return _arr[rhs];}

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

        // modifiers
        //assigns the range between first and last to this container in the same order 
        // and destroys old content if its outside the distance of the range
        // size get updated to the distance between range so it fits
        template <class InputIterator>
        void assign (InputIterator first, InputIterator last)
        {
            size_type dis = last - first;
            size_type position = 0;

            if (dis > _size)
                reserve(dis);
            for (position = 0; first != last; first++)
                al.construct(&_arr[position++], *first);
            for (; position < _size; position++)
                al.destroy(&_arr[position]);
            _size = dis;
        }
        // if n  < size dont deallocate leaves the old capacity
        void 			assign (size_type n, const value_type& val)
        {
			if (n > _size)
				reserve(n);
			_size = n;
			for (size_type i = 0; i < _size ; i++)
				al.construct(&_arr[i], val);
		}


        void push_back (const value_type& val)
        {
            if(_size == 0)
                reserve(1);
            if (_size == _capacity)
            {
                reserve(_capacity * 2);
            }
            al.construct(&_arr[_size], val);
            _size++;
        }
        void pop_back() {
			al.destroy(&_arr[_size - 1]);
			_size--;
		}

        //inserts

        // this inserts in the position
        iterator insert (iterator position, const value_type& val)
        {
            size_type dist = position - begin();
            if (_size == 0)
                reserve(1);
            else if (_size + 1 > _capacity)
                reserve(_capacity * 2);
            if (_size == 0)
				al.construct(&_arr[_size++], val);
            else
            {
                for (size_type i = _size - 1 ; i > dist ; i--)
					al.construct(&_arr[i + 1], _arr[i]);
                al.construct(&_arr[dist], val);
                _size++;
            }
            return(begin() + dist);
        }
        // this insert the value staring from the position n times
        void insert (iterator position, size_type n, const value_type& val)
        {
            size_type start =  position - begin();
            if (_size + n > _capacity)
            {
				if (n > _size)
					reserve(_size + n);
				else
					reserve(_capacity * 2);
            }
            if (_size == 0)
				for (size_type i = 0; i < n ; i++)
					al.construct(&_arr[i], val);
            else
            {
                for (size_type i = _size - 1 ; i >= start ; i--)
					al.construct(&_arr[i + n], _arr[i]);
                for (size_type i = 0; i < n; i++)
                    al.construct(&_arr[start + i], val);
            }
            _size += n;
        }
        //this one puts the range between first and last starting from the position
        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last)
        {
            size_type dist = first - last;
            size_type start =  position - begin();
            if (_size + dist > _capacity)
            {
                if (dist > _size)
                    reserve(_size + dist);
                else
                    reserve(_capacity * 2);
			}
            if (_size == 0)
            {
                size_type i = 0;
                while (first != last)
                {
                    al.construct(&_arr[i], *first);
                    first++;
                    i++;
                }
            }
            else
            {
                for (size_type i = _size - 1 ; i >= start  ; i--)
					al.construct(&_arr[i + dist], _arr[i]);
                for (size_type i = 0; i < dist; i++)
                {
                    al.construct(&_arr[start + i], *first);
                    first++;
                }
            }
            _size += dist;
        }
        //erase , this one erases an element
        iterator		erase (iterator position)
        {
            size_type i = position - begin();
            
			while (i < _size - 1 )
            {
				al.construct(&_arr[i], _arr[i + 1]);
                i++;
            }
            al.destroy(&_arr[_size - 1]);
			_size--;
			return (position);
		}
        //this one erases all the elements from first to last
        iterator 		erase (iterator first, iterator last) {
			// TO-DO: Destroy elements from first to last.
			size_type dist = last - first;
			size_type start = first = begin();

			for (size_type i = 0; i < dist ; i++ )
				al.construct(&_arr[start + i], _arr[--_size]);
			for (size_type i = 0 ; i > dist ; i++)
				al.destroy(&_arr[start + i]);
			return (first);
		}

        //swap changes content of this container by the content of x so we just use std::swap that is offered
        void swap (Vector& x)
        {
            std::swap(_arr, x._arr);
            std::swap(_size, x._size);
            std::swap(_capacity, x._capacity);
            //this is not needed since vectors have the same type
            std::swap(al, x.al);
        }

        allocator_type get_allocator() const
        {
            return(allocator_type());
        }
        size_type Get_Size(){return this->_size;}
        private:
            allocator_type al;
            value_type *_arr;
            size_type _size;
            size_type _capacity;

    };

    template <class T, class Alloc>
    bool operator== (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return (lhs.size() == rhs.size());
        return (std::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template <class T, class Alloc>
    bool operator!= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
    {
        return(!(lhs == rhs));
    }

    template <class T, class Alloc>
    bool operator<  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
    {
        return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    template <class T, class Alloc>
    bool operator> (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
    {
        return(!(lhs < rhs));
    }
    template <class T, class Alloc>
    bool operator<= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
    {
        if (lhs < rhs || lhs == rhs)
            return(true);
        return (false);
    }
    template <class T, class Alloc>
    bool operator>= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
    {
        if (lhs > rhs || lhs == rhs)
            return(true);
        return (false);
    }
};