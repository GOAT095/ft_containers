#include "map.hpp"
#include <map>
bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

int main ()
{
  // ft::Map<char,int> first;

  // first['a']=10;
  // first['b']=30;
  // first['c']=50;
  // first['d']=70;

  // ft::Map<char,int> second (first.begin(),first.end());

  // ft::Map<char,int> third (second);

  // ft::Map<char,int,classcomp> fourth;                 // class as Compare

  // bool(*fn_pt)(char,char) = fncomp;
  // ft::Map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare
  // ft::Map<char, int> first;
   ft::Map<char,int> mymap;

  // first insert function version (single parameter):
  mymap.insert ( ft::pair<char,int>('a',100) );
  mymap.insert ( ft::pair<char,int>('z',200) );

  ft::pair<ft::Map<char,int>::iterator,bool> ret;
  ret = mymap.insert ( ft::pair<char,int>('z',500) );
  if (ret.second==false) {
    std::cout << "element 'z' already existed";
    std::cout << " with a value of " << ret.first->second << '\n';
  }

  // second insert function version (with hint position):
  ft::Map<char,int>::iterator it = mymap.begin();
  mymap.insert (it, ft::pair<char,int>('b',300));  // max efficiency inserting
  mymap.insert (it, ft::pair<char,int>('c',400));  // no max efficiency inserting

  // third insert function version (range insertion):
  ft::Map<char,int> anothermap;
  anothermap.insert(mymap.begin(),mymap.find('c'));

  // showing contents:
  std::cout << "mymap contains:\n";
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  std::cout << "anothermap contains:\n";
  for (it=anothermap.begin(); it!=anothermap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
  return 0;
}
// int main(){

//   // ft::Map<char,int> foo,bar;
//   // foo['a']=100;
//   // foo['b']=200;
//   // bar['a']=10;
//   // bar['z']=1000;

//   // // foo ({{a,100},{b,200}}) vs bar ({a,10},{z,1000}}):
//   // if (foo==bar) std::cout << "foo and bar are equal\n";
//   // if (foo!=bar) std::cout << "foo and bar are not equal\n";
//   // if (foo< bar) std::cout << "foo is less than bar\n";
//   // if (foo> bar) std::cout << "foo is greater than bar\n";
//   // if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
//   // if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

//   // ft::Map<char,int> foo,bar;

//   // foo['x']=100;
//   // foo['y']=200;

//   // bar['a']=11;
//   // bar['b']=22;
//   // bar['c']=33;

//   // foo.swap(bar);

//   // std::cout << "foo contains:\n";
//   // for (ft::Map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
//   //   std::cout << it->first << " => " << it->second << '\n';

//   // std::cout << "bar contains:\n";
//   // for (ft::Map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
//   //   std::cout << it->first << " => " << it->second << '\n';

//   // ft::Map<char,int> mymap;

//   // mymap['a']=10;
//   // mymap['b']=20;
//   // mymap['c']=30;

//   // ft::pair<ft::Map<char,int>::iterator,ft::Map<char,int>::iterator> ret;
//   // ret = mymap.equal_range('b');

//   // std::cout << "lower bound points to: ";
//   // std::cout << ret.first->first << " => " << ret.first->second << '\n';

//   // std::cout << "upper bound points to: ";
//   // std::cout << ret.second->first << " => " << ret.second->second << '\n';


//   // ft::map<char,int> mymap;
//   // ft::map<char,int>::iterator itlow,itup;

//   // mymap['a']=20;
//   // mymap['b']=40;
//   // mymap['c']=60;
//   // mymap['d']=80;
//   // mymap['e']=100;

//   // itlow=mymap.lower_bound ('a');  // itlow points to b
//   // itup=mymap.upper_bound ('e');   // itup points to e (not d!)
  
//   // mymap.erase(itlow,itup);        // erases [itlow,itup)
//   // ft::map<char,int>::iterator it=mymap.begin();
//   // // print content:
//   // for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
//   //   std::cout << it->first << " => " << it->second << '\n';

// //     ft::map<char,int> mymap;
// //   char c;

// //   mymap ['a']=101;
// //   mymap ['c']=202;
// //   mymap ['f']=303;

// //   for (c='a'; c<'h'; c++)
// //   {
// //     std::cout << c;
// //     if (mymap.count(c)>0)
// //       std::cout << " is an element of mymap.\n";
// //     else 
// //       std::cout << " is not an element of mymap.\n";
// //   }

// // }

// //    ft::map<char,int> mymap;
// //   ft::map<char,int>::iterator it;

// //   mymap['a']=50;
// //   mymap['b']=100;
// //   mymap['c']=150;
// //   mymap['d']=200;

// //   it = mymap.find('b');
// //   if (it != mymap.end())
// //     mymap.erase (it);

// //   // print content:
// //   std::cout << "elements in mymap:" << '\n';
// //   std::cout << "a => " << mymap.find('a')->second << '\n';
// //   std::cout << "c => " << mymap.find('c')->second << '\n';
// //   std::cout << "d => " << mymap.find('d')->second << '\n';

// // {    
// //       ft::map<char,int> mymap;

// //   mymap['x']=100;
// //   mymap['y']=200;
// //   mymap['z']=300;

// //   std::cout << "mymap contains:\n";
// //   for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
// //     std::cout << it->first << " => " << it->second << '\n';

// //   mymap.clear();
// //   mymap['a']=1101;
// //   mymap['b']=2202;

// //   std::cout << "mymap contains:\n";
// //   for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
// //     std::cout << it->first << " => " << it->second << '\n';
    
// //     }
//     ft::Map<int, int> m;
//     m.insert(ft::pair<int,int>(1,3));
//     m.insert(ft::pair<int,int>(10,3));
//     m.insert(ft::pair<int,int>(2,3));
//     m.insert(ft::pair<int,int>(3,3));
//     m.insert(ft::pair<int,int>(4,3));
//     m.insert(ft::pair<int,int>(5,3));
//     m.insert(ft::pair<int,int>(6,3));
//     m.insert(ft::pair<int,int>(7,3));
//     m.insert(ft::pair<int,int>(8,3));
//     m.insert(ft::pair<int,int>(-1,3));
//     m.insert(ft::pair<int,int>(-3,3));
//     m.insert(ft::pair<int,int>(-4,3));
//     ft::Map<int, int>::iterator it = m.begin();
//     ft::Map<int, int>::iterator it2 = m.end();
//     it2--;
//     it2--;
//     it2--;
//     // std::cout << it2->first << ft::endl;
//     m.erase(it, it2);
//     // m.printTree()
//     it = m.begin();
//     // std::cout << it->first << ft::endl;
//     // for (; it != m.end(); ++it){
//     //     std::cout << it->first << ft::endl;
//     // }
//     it = m.end();
//     it--;
//     // std::cout << it->first << ft::endl;
//     for (it; it != m.begin(); --it){
//         std::cout << it->first << ft::endl;
//     }
//     // it++;
//     it++;it++;it++;it++;it++;it++;it++;it++;it++;it++;it++;it++;it++;it++;it++;
    
    
//     return 0;
// }