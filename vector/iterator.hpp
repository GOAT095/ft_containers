
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
  class Iterator {
    public:
      typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type value_type;
      typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type  difference_type;
      typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer   pointer;
      typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference reference;
      typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category  iterator_category;
      //default
        Iterator():p(nullptr){};
      //pointer
        Iterator(const pointer &ptr) : p(ptr){};
      //copy
        Iterator(const Iterator& copy){*this = copy;}
      //oprator =
        Iterator &operator = (const Iterator &copy)
        {
          this->p = copy.p;
        }
        //table
    friend bool operator==(const Iterator& lhs, const Iterator& rhs)  {return lhs.p == rhs.p;}      
    friend bool operator!=(const Iterator& lhs, const Iterator& rhs)  {return lhs.p != rhs.p;}
    friend bool operator>(const Iterator& lhs, const Iterator& rhs)  {return lhs.p > rhs.p;}
    friend bool operator<(const Iterator& lhs, const Iterator& rhs)  {return lhs.p < rhs.p;}
    friend bool operator>=(const Iterator& lhs, const Iterator& rhs)  {return lhs.p >= rhs.p;}
    friend bool operator<=(const Iterator& lhs, const Iterator& rhs)  {return lhs.p <= rhs.p;}

    pointer& operator*() const {return *p;}
    pointer* operator->() const {return p;}

    // wtf is this one

    //post
    Iterator operator++(int) const {Iterator tmp(*this); ++p; return tmp;}
    Iterator operator--(int) const {Iterator tmp(*this); --p; return tmp;}

    //pre
    Iterator& operator++() {++p; return *this;}
    Iterator& operator--() {--p; return *this;}

    //additin and sub
    Iterator& operator+=(difference_type rhs) {p += rhs; return *this;}
    Iterator& operator-=(difference_type rhs) {p -= rhs; return *this;}

    // brackets
    pointer& operator[](difference_type rhs) const {return p[rhs];}

    private:
      pointer p;

  };
  // Operators : mis

}