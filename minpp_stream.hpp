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

  bool  test() const;
  bool  test_char(char  c) const;

  void  advance(int  n=1);

  Position  get_position() const;

  bool  try_read(const char*  s);

  void  print(int  line_length=1) const;

};


}


#endif




