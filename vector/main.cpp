// #include "iterator.hpp"
#include "Vector.hpp"
#include "stack"
int main (void)
{
    // int i = 0;
    ft::Vector<int> myvector(5);
    for(int i = 0; i < 5; i++)
        myvector[i] = i;
    ft::Vector<int>::iterator it =  myvector.begin();
    for(int i = 0; i < 5; i++)
    {   std::cout << *it; it++;}
    ft::Vector<int>::iterator it2 =  myvector.end();
    std::cout << *(--it2) << std::endl;

    // working fine as expected !

    std::cout << myvector.size() << std::endl;
    std::cout << myvector.max_size() << std::endl;;
    std::cout << myvector.capacity() << std::endl;;

    //working fine
    return 0;
}