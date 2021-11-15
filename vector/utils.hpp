#pragma once
#include <iostream>

 //is_integral
    template< class T >
    struct is_integral
    {
      bool value = false;
    }
    
    is_integral <int>                 {  value = true; };
    is_integral <unsigned int>        {  value = true; };
    is_integral <long>                {  value = true; };
    is_integral <unsigned long>       {  value = true; };
    is_integral <long long>           {  value = true; };
    is_integral <unsigned long long>  {  value = true; };
    is_integral <short>               {  value = true; };
    is_integral <wchar_t>             {  value = true; };
    is_integral <char>                {  value = true; };
    is_integral <bool>                {  value = true; };
    