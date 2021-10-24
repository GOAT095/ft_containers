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
      iterator(const itearator& copy){*this = copy;}
    //oprator =
      iterator &operator = (const iterator &copy)
      {
        this->p = copy.p;
      }
    private:
      T *p;
  };
};