#ifndef MINPP_ELEMENT_HPP_INCLUDED
#define MINPP_ELEMENT_HPP_INCLUDED


#include"minpp_position.hpp"



namespace minpp{



constexpr uint16_t  nullid = 0xFFFF;


struct
Element
{
  Position  position;

  uint16_t  id_index;

  char16_t  unicode;


  Element(Position  pos, uint16_t  i=0, char16_t  c=0);

  void  print(FILE*  f=stdout, bool  verbose=false) const;

};


}


#endif




