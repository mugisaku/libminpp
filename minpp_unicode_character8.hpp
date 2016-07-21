#ifndef MINPP_UNICODE_CHARACTER_HPP_INCLUDED
#define MINPP_UNICODE_CHARACTER_HPP_INCLUDED


#include<string>


namespace minpp{


struct
Character8
{
  char  codes[4];

  Character8(char16_t  c=0);

  Character8&  operator=(char16_t  c);

};


}




#endif




