#pragma once

#include <cstddef>
#include <iostream>

namespace ft
{
  template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
      struct iterator {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
      };
  template <class T>
  class MyIterator {
    public:
          typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type value_type;
          typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type  difference_type;
          typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer   pointer;
          typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference reference;
          typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category  iterator_category;

          // typedef MyIterator<T> iterator;
      //default
        MyIterator():p(nullptr){};
      //pointer
        MyIterator(const pointer &ptr) : p(ptr){};
      //copy
        MyIterator(const MyIterator& copy){*this = copy;}
      //oprator =
        MyIterator &operator = (const MyIterator &copy)
        {
          this->p = copy.p;
          return(*this);
        }
        //table
    pointer GetPointer() const{return p;}
  

    reference operator*() const {return *p;}
    pointer operator->() const {return p;}


    //post
    MyIterator operator++(int)  {MyIterator tmp(*this); ++p; return tmp;}
    MyIterator operator--(int)  {MyIterator tmp(*this); --p; return tmp;}

    //pre
    MyIterator& operator++() {++p; return *this;}
    MyIterator& operator--() {--p; return *this;}

    //additin and sub
    MyIterator& operator+=(difference_type rhs) {p += rhs; return *this;}
    MyIterator& operator-=(difference_type rhs) {p -= rhs; return *this;}

    //arithmetic operators + and -
    MyIterator operator+(difference_type rhs)  {return MyIterator(p+rhs);}
    MyIterator operator-(difference_type rhs)  {return MyIterator(p-rhs);}

    difference_type operator-(MyIterator rhs)  {return (p - rhs.p);}
    
    // element access
    reference& operator[](difference_type rhs)  {return p[rhs];}

    operator MyIterator<const T>() const {
                return (MyIterator<const T>(this->p));
            }
    friend  MyIterator operator+( MyIterator::difference_type n,MyIterator rhs)
    {
        return(MyIterator(rhs.p + n));
    }

    private:
      pointer p;

  };
  // Operators : mis
    template <typename T>
      bool operator==(const MyIterator<T>& lhs, const MyIterator<T>& rhs)  {return lhs.GetPointer() == rhs.GetPointer();}
    template <typename T>      
      bool operator!=(const MyIterator<T>& lhs, const MyIterator<T>& rhs)  {return lhs.GetPointer() != rhs.GetPointer();}
    template <typename T>
      bool operator>(const MyIterator<T>& lhs, const MyIterator<T>& rhs)  {return lhs.GetPointer() > rhs.GetPointer();}
    template <typename T>
      bool operator<(const MyIterator<T>& lhs, const MyIterator<T>& rhs)  {return lhs.GetPointer() < rhs.GetPointer();}
    template <typename T>
      bool operator>=(const MyIterator<T>& lhs, const MyIterator<T>& rhs)  {return lhs.GetPointer() >= rhs.GetPointer();}
    template <typename T>
      bool operator<=(const MyIterator<T>& lhs, const MyIterator<T>& rhs)  {return lhs.GetPointer() <= rhs.GetPointer();}
}