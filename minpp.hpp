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
ErrorOnIncludeOnce
{
};



ElementList  open(const char*  path, Index  parent_id_index=nullidx, bool  once=false);

bool  test_id(const std::string&  id);

const std::string&  get_id(Index  i);
const char*         get_text(Index  i);

Stream  create_stream_from_file(const char*  path);

void  print(const ElementList&  ls, FILE*  f=stdout, bool  verbose=false);


}




#endif




