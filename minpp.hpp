#ifndef MINPP_HPP_INCLUDED
#define MINPP_HPP_INCLUDED


#include<string>
#include<vector>
#include"minpp_element.hpp"
#include"minpp_stream.hpp"



namespace minpp{


using ElementList = std::vector<Element>;


struct
ErrorOnOperateFile
{
};


struct
ErrorOnOpenFile: ErrorOnOperateFile
{
};


struct
ErrorOnReadFile: ErrorOnOperateFile
{
};


struct
ErrorOnInclude
{
};


struct
ErrorOnReadRange
{
  const Stream  stream;

  uint16_t  id_index;

  int  printed;

  ErrorOnReadRange(const Stream&  s, uint16_t  i=nullid):
  stream(s),
  id_index(i),
  printed(0){}

};



ElementList  open(const char*  path, uint16_t  parent_id_index=nullid);

void  print(const ElementList&  ls, FILE*  f=stdout, bool  verbose=false);


}




#endif




