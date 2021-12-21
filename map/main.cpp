#include "map.hpp"
#include <map>
bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs>rhs;}
};

int main ()
{
  
std::map<char, int> m;
        ft::Map<char, int> ft_m;
        std::map<char, int>::iterator it;
        ft::Map<char, int>::iterator ft_it;

        // insert some values:
        ft_m['a'] = 10;
        ft_m['b'] = 20;
        ft_m['c'] = 30;
        ft_m['d'] = 40;
        ft_m['e'] = 50;
        ft_m['f'] = 60;

        m['a'] = 10;
        m['b'] = 20;
        m['c'] = 30;
        m['d'] = 40;
        m['e'] = 50;
        m['f'] = 60;

        it = m.find('b');
        ft_it = ft_m.find('b');

        m.erase(it);       // erasing by iterator
        ft_m.erase(ft_it); // erasing by iterator

        int ret = m.erase('c');       // erasing by key
        int ft_ret = ft_m.erase('c'); // erasing by key


        it = m.find('e');
        ft_it = ft_m.find('e');


        m.erase(it, m.end());          // erasing by range
        ft_m.erase(ft_it, ft_m.end()); // erasing by range

  return 0;
}
  // std::map<int, std::string> m1;
  //       ft::Map<int, std::string> ft_m1;

  //       for (size_t i = 0; i < 10; i++)
  //       {
  //           m1.insert(std::make_pair(i, "string2"));
  //           ft_m1.insert(ft::make_pair(i, "string2"));
  //       }

  //       std::map<int, std::string> const m2(m1.rbegin(), m1.rend());
  //       ft::Map<int, std::string> const ft_m2(ft_m1.rbegin(), ft_m1.rend());

  //       /*-----------------------------------------------------*/
  //       /*------------------ ft::Maps ---------------------*/
  //       /*----------------------------------------------------*/
  //       /*------------------ strings to store the results ----*/
  //       std::string res, ft_res, c_res, c_ft_res;
  //       /*----------------------------------------------------*/
  //       for (std::map<int, std::string>::reverse_iterator it = m1.rbegin(); it != m1.rend(); ++it) // fill res from m1
  //           res += it->second;
  //       for (std::map<int, std::string>::const_reverse_iterator rit = m2.rbegin(); rit != m2.rend(); ++rit) // fill c_res from const m1
  //           c_res += rit->second;

  //       for (ft::Map<int, std::string>::reverse_iterator it = ft_m1.rbegin(); it != ft_m1.rend(); ++it) // fill ft_res from ft_m1
  //           ft_res += it->second;
  //       for (ft::Map<int, std::string>::const_reverse_iterator rit = ft_m2.rbegin(); rit != ft_m2.rend(); ++rit) // fill c_ft_res from const ft_m1
  //           c_ft_res += rit->second;

        // ft::Map<int, int>::reverse_iterator rit = fourth.rend();
        // rit--;
  // ft::Map<char,int> mymap;
  // ft::Map<char,int>::iterator itlow,itup;

  // mymap['a']=20;
  // mymap['b']=40;
  // mymap['c']=60;
  // mymap['d']=80;
  // mymap['e']=100;

  // itlow=mymap.lower_bound ('b');  // itlow points to b
  // itup=mymap.upper_bound ('d');   // itup points to e (not d!)

  // mymap.erase(itlow,itup);        // erases [itlow,itup)

  // // print content:
  // for (ft::Map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
  //   std::cout << it->first << " => " << it->second << '\n';

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