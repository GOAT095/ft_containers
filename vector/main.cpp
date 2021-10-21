#include "Vector.hpp"
#include "stack"
int main (void)
{
    std::allocator<int> ttt;
    ft::allocate_memory_vector(ttt, 10);
    // ft::deallocate_memory(ttt, 10);
    return 0;
}