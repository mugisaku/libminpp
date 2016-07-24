#ifndef MINPP_STREAM_HPP_INCLUDED
#define MINPP_STREAM_HPP_INCLUDED


#include"minpp_character.hpp"
#include"minpp_folder.hpp"



namespace minpp{


struct
ErrorOnReadFile
{
};


class
Stream
{
  Position  position;

  std::string  source;

  const char*  pointer;

  Index  id_index;

public:
  Stream();
  Stream(FILE*  f);
  Stream(std::string&&  source_);


  void  reset(std::string&&  source_);
  void  reset(FILE*  f);

  std::string  read_id();

  char16_t  get_char16();

  bool  test() const;
  bool  test_char(char  c) const;

  Index  get_id_index() const;
  void  change_id_index(Index  i);

  const Text*  get_text() const;

  void  advance(int  n=1);

  Position  get_position() const;

  bool  try_read(const char*  s);

  void  print(int  line_length=1) const;

};


struct
ErrorOnProcessStream
{
  const Stream  stream;

  int  printed;

  ErrorOnProcessStream(const Stream&  s):
  stream(s),
  printed(0){}

};


}


#endif




