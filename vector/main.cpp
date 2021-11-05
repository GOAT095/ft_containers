// #include "iterator.hpp"
#include "Vector.hpp"
#include "stack"
int main (void)
{
    // int i = 0;
    ft::Vector<int> myvector(5);
    for(int i = 0; i < 5; i++)
        myvector[i] = i;
    // ft::Vector<int>::iterator it =  myvector.begin();
    // for(int i = 0; i < 5; i++)
    //     printf("%d", *it);it++;
    ft::Vector<int>::iterator it =  myvector.end();
    printf("%d", *it);
    return 0;
}