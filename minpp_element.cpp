#include"minpp_element.hpp"
#include"minpp_unicode.hpp"
#include"minpp_unicode_character8.hpp"
#include"minpp_idtable.hpp"
#include<cstdio>




namespace minpp{




Element::
Element(Position  pos, uint16_t  i, char16_t  c):
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


  Character8  c8(unicode);

  fprintf(f,"%s",c8.codes);
}


}




