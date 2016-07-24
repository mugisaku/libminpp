#ifndef MINPP_CHARACTER_HPP_INCLUDED
#define MINPP_CHARACTER_HPP_INCLUDED


#include"minpp_position.hpp"
#include<string>



namespace minpp{


using Index = uint16_t;

constexpr uint16_t  nullidx = 0;


struct
Character
{
  Position  position;

  Index  id_index;

  char16_t  unicode;


  Character(Position  pos=Position(), Index  i=0, char16_t  c=0);

  void  print(FILE*  f=stdout, bool  verbose=false) const;

};


}


#endif




