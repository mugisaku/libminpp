#ifndef MINPP_HPP_INCLUDED
#define MINPP_HPP_INCLUDED


#include<string>
#include<vector>
#include"minpp_element.hpp"



namespace minpp{


using ElementList = std::vector<Element>;


ElementList  open(const char*   path);

void  print(const ElementList&  ls, FILE*  f=stdout, bool  verbose=false);


}




#endif




