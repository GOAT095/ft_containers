#include "Vector.hpp"


namespace ft
{

    template <class  Category, class T, class Distance = ptrdiff_t,
            class Pointer = T*, class Reference = T&>
    struct iterator_source {
      typedef T         value_type;
      typedef Distance  difference_type;
      typedef Pointer   pointer;
      typedef Reference reference;
      typedef Category  iterator_category;
  };

  template <typename T>
  class iterator : public iterator_source<std::random_access_iterator_tag, T>
  {
    public:
    //default
      iterator():p(nullptr){};
    //pointer
      iterator(const T &ptr) : this->p(ptr){};
    //copy
      iterator(const iterator& copy){*this = copy;}
    //oprator =
      iterator &operator = (const iterator &copy)
      {
        this->p = copy.p;
      }
      //table
        //bools
          bool operator==(iterator const& it1, iterator const& it2)	{ return (it1.p == it2.p);	}
          bool operator!=(iterator const& it1, iterator const& it2)	{ return (it1.p != it2.p);	}
          bool operator<(iterator const& it1, iterator const& it2)	{ return (it1.p < it2.p);		}
          bool operator>(iterator const& it1, iterator const& it2)	{ return (it1.p > it2.p);		}
          bool operator<= (iterator const& it1, iterator const& it2){ return (it1.p <= it2.p);	}
          bool operator>= (iterator const& it1, iterator const& it2){ return (it1.p >= it2.p);	}
        
          iterator &operator +=(const size_t n) {return iterator(this->p + n); }
          iterator& operator++() {++p; return *this;}
          T &operator*() const { return *p; }
          T *operator->() const {return p;}
          T &operator[](Distance rhs) const {return (p[rhs]);}
    private:
      T *p;
    
   
  };
    friend  iterator operator+(difference_type lhs, const iterator& rhs) {return iterator(lhs+rhs.p);}
    friend  iterator operator-(difference_type lhs, const iterator& rhs) {return iterator(lhs-rhs.p);}
};