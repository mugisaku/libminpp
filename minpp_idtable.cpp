#include"minpp_idtable.hpp"
#include<vector>




namespace minpp{


namespace{


std::vector<std::string>
table;


}


int
append_id(std::string&&  id)
{
  int  i = 0;

    for(auto&  ent: table)
    {
        if(ent == id)
        {
          return i;
        }


      ++i;
    }


  table.emplace_back(std::move(id));

  return i;
}


bool
test_id(const std::string&  id)
{
    for(auto&  ent: table)
    {
        if(ent == id)
        {
          return true;
        }
    }


  return false;
}


const std::string&
get_id(int  i)
{
  return table[i];
}



}




