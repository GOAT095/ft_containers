#include "map.hpp"
#include <map>
int main(){

  ft::map<char,int> mymap;

  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;

  ft::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ret;
  ret = mymap.equal_range('b');

  std::cout << "lower bound points to: ";
  std::cout << ret.first->first << " => " << ret.first->second << '\n';

  std::cout << "upper bound points to: ";
  std::cout << ret.second->first << " => " << ret.second->second << '\n';


  // ft::map<char,int> mymap;
  // ft::map<char,int>::iterator itlow,itup;

  // mymap['a']=20;
  // mymap['b']=40;
  // mymap['c']=60;
  // mymap['d']=80;
  // mymap['e']=100;

  // itlow=mymap.lower_bound ('a');  // itlow points to b
  // itup=mymap.upper_bound ('e');   // itup points to e (not d!)
  
  // mymap.erase(itlow,itup);        // erases [itlow,itup)
  // ft::map<char,int>::iterator it=mymap.begin();
  // // print content:
  // for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
  //   std::cout << it->first << " => " << it->second << '\n';

//     ft::map<char,int> mymap;
//   char c;

//   mymap ['a']=101;
//   mymap ['c']=202;
//   mymap ['f']=303;

//   for (c='a'; c<'h'; c++)
//   {
//     std::cout << c;
//     if (mymap.count(c)>0)
//       std::cout << " is an element of mymap.\n";
//     else 
//       std::cout << " is not an element of mymap.\n";
//   }

// }

//    ft::map<char,int> mymap;
//   ft::map<char,int>::iterator it;

//   mymap['a']=50;
//   mymap['b']=100;
//   mymap['c']=150;
//   mymap['d']=200;

//   it = mymap.find('b');
//   if (it != mymap.end())
//     mymap.erase (it);

//   // print content:
//   std::cout << "elements in mymap:" << '\n';
//   std::cout << "a => " << mymap.find('a')->second << '\n';
//   std::cout << "c => " << mymap.find('c')->second << '\n';
//   std::cout << "d => " << mymap.find('d')->second << '\n';

// {    
//       ft::map<char,int> mymap;

//   mymap['x']=100;
//   mymap['y']=200;
//   mymap['z']=300;

//   std::cout << "mymap contains:\n";
//   for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
//     std::cout << it->first << " => " << it->second << '\n';

//   mymap.clear();
//   mymap['a']=1101;
//   mymap['b']=2202;

//   std::cout << "mymap contains:\n";
//   for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
//     std::cout << it->first << " => " << it->second << '\n';
    
//     }
    // ft::map<int, int> m;
    // m.insert(ft::pair<int,int>(1,3));
    // m.insert(ft::pair<int,int>(10,3));
    // m.insert(ft::pair<int,int>(2,3));
    // m.insert(ft::pair<int,int>(3,3));
    // m.insert(ft::pair<int,int>(4,3));
    // m.insert(ft::pair<int,int>(5,3));
    // m.insert(ft::pair<int,int>(6,3));
    // m.insert(ft::pair<int,int>(7,3));
    // m.insert(ft::pair<int,int>(8,3));
    // m.insert(ft::pair<int,int>(-1,3));
    // m.insert(ft::pair<int,int>(-3,3));
    // m.insert(ft::pair<int,int>(-4,3));
    // ft::map<int, int>::iterator it = m.begin();
    // ft::map<int, int>::iterator it2 = m.end();
    // it2--;
    // it2--;
    // it2--;
    // // std::cout << it2->first << std::endl;
    // m.erase(it, it2);
    // // m.printTree()
    // it = m.begin();
    // // std::cout << it->first << std::endl;
    // for (; it != m.end(); ++it){
    //     std::cout << it->first << std::endl;
    // }
    // it = m.end();
    // it--;
    // std::cout << it->first << std::endl;
    // for (it; it != m.begin(); --it){
    //     std::cout << it->first << std::endl;
    // }
    //it++;
    //it++;it++;it++;it++;it++;it++;it++;it++;it++;it++;it++;it++;it++;it++;it++;
    
    
    return 0;
}