#ifndef MINPP_IDTABLE_HPP_INCLUDED
#define MINPP_IDTABLE_HPP_INCLUDED


#include<string>


namespace minpp{


int  append_id(std::string&&  id);
bool  test_id(const std::string&  id);
const std::string&  get_id(int  i);


}




#endif




