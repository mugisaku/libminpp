#ifndef MINPP_STRING_HPP_INCLUDED
#define MINPP_STRING_HPP_INCLUDED


#include"minpp_character.hpp"
#include<vector>



namespace minpp{


struct
ErrorOnOpenFile
{
};


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
  void  open(const char*  path);

  std::string  to_stdstring() const;

  void  print(FILE*  f=stdout, bool  verbose=false) const;

};


}


#endif




