#ifndef MINPP_STREAM_HPP_INCLUDED
#define MINPP_STREAM_HPP_INCLUDED


#include"minpp_position.hpp"
#include<string>



namespace minpp{


class
Stream
{
  Position  position;

  const char*  pointer;

public:
  Stream(const char*  p=nullptr);

  char16_t  get_char16();

  void  advance(int  n=1);

  Position  get_position() const;

  bool  try_read(const char*  s);

  std::string  read_string_until(char  c);

};


}


#endif




