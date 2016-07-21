#include"minpp_position.hpp"
#include<cstdio>




namespace minpp{




Position::
Position(uint16_t  ln, uint16_t  cn):
line_number(ln),
column_number(cn)
{
}




void
Position::
print(FILE*  f) const
{
  fprintf(f,"行:%4d 列:%4d",line_number+1,column_number+1);
}


}




