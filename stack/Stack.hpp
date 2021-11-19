/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <anassif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 04:04:23 by anassif           #+#    #+#             */
/*   Updated: 2021/11/19 23:01:49 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vector/Vector.hpp"

namespace ft{
    
    template <class T, class Container = ft::Vector<T> >
    class Stack
    {
        public:
        
            explicit Stack (const container_type& ctnr = container_type());

            typedef size_t size_type;
            typedef Container container_type;
            typedef T value_type;

            bool empty() const{return (_container->size() == 0);}
            size_type size() const{return (_container->size());}
            value_type& top(){return (_container->back());}
            const value_type& top() const{return (_container->back());}
            void push (const value_type& val){_container->push_back(val);}
            void pop(){_container->pop_back();}
            
            
        private:
            value_type *_container;
    };
    template <class T, class Container>
    bool operator== (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs);

    template <class T, class Container>
    bool operator!= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs);
        
    template <class T, class Container>
    bool operator<  (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs);

    template <class T, class Container>
    bool operator<= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs);

    template <class T, class Container>
    bool operator>  (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs);

    template <class T, class Container>
    bool operator>= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs);
}