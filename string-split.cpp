/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <string>
#include "string-split.h"

void string_split( const std::string& s, char delim, std::vector< std::string >& v )
{
    auto i = 0;
    auto pos = s.find(delim);
    const std::string str_delim( &delim );
    v.erase( v.begin(), v.end() );
    while( pos != std::string::npos )
    {
      if( s.substr(i, pos-i) != str_delim &&
          s.substr(i, pos-i) != "" )
         v.push_back(s.substr(i, pos-i) );
      i = ++pos;
      pos = s.find(delim, pos);

      if( pos == std::string::npos )
         v.push_back(s.substr(i, s.length()));
    }
}