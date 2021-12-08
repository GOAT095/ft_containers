#include "map.hpp"

int main(){

    ft::map<int, int> m;
    m.insert(ft::pair<int,int>(1,3));
    m.insert(ft::pair<int,int>(10,3));
    m.insert(ft::pair<int,int>(2,3));
    m.insert(ft::pair<int,int>(3,3));
    m.insert(ft::pair<int,int>(4,3));
    m.insert(ft::pair<int,int>(5,3));
    m.insert(ft::pair<int,int>(6,3));
    m.insert(ft::pair<int,int>(7,3));
    m.insert(ft::pair<int,int>(8,3));
    m.insert(ft::pair<int,int>(-1,3));
    m.insert(ft::pair<int,int>(-3,3));
    m.insert(ft::pair<int,int>(-4,3));
    // m.printTree()
    ft::map<int, int>::iterator it = m.begin();
    
    for (it; it != m.end(); ++it){
        std::cout << it->first << std::endl;
    }
    //it++;
    //it++;it++;it++;it++;it++;it++;it++;it++;it++;it++;it++;it++;it++;it++;it++;
    
    
    return 0;
}