#ifndef MINPP_STRING_HPP_INCLUDED
#define MINPP_STRING_HPP_INCLUDED


#include"minpp_character.hpp"
#include"minpp_stream.hpp"
#include<vector>



namespace minpp{


struct
ErrorOnInclude
{
};


struct
ErrorOnIncludeOnce
{
};




class
String: public std::vector<Character>
{

public:
  explicit String(Stream&  s);

  std::string  to_stdstring() const;

  void  print(FILE*  f=stdout, bool  verbose=false) const;

};


}


#endif




