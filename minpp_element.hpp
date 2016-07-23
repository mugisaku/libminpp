#ifndef MINPP_ELEMENT_HPP_INCLUDED
#define MINPP_ELEMENT_HPP_INCLUDED


#include"minpp_position.hpp"
#include<string>



namespace minpp{


using Index = uint16_t;

constexpr uint16_t  nullidx = 0xFFFF;


struct
Element
{
  Position  position;

  Index  id_index;

  char16_t  unicode;


  Element(Position  pos, Index  i=0, char16_t  c=0);

  void  print(FILE*  f=stdout, bool  verbose=false) const;

};


}


#endif




