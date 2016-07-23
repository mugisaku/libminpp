#include"minpp_element.hpp"
#include"minpp_unicode.hpp"
#include"minpp_utf8chunk.hpp"
#include"minpp.hpp"
#include<cstdio>




namespace minpp{




Element::
Element(Position  pos, Index  i, char16_t  c):
position(pos),
id_index(i),
unicode(c)
{
}




void
Element::
print(FILE*  f, bool  verbose) const
{
    if(verbose)
    {
      fprintf(f,"[");

      position.print();

      fprintf(f," %s]: ",get_id(id_index).data());
    }


  UTF8Chunk  chk(unicode);

  fprintf(f,"%s",chk.codes);
}


}




