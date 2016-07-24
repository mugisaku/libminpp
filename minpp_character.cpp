#include"minpp_character.hpp"
#include"minpp_unicode.hpp"
#include"minpp_utf8chunk.hpp"
#include"minpp_folder.hpp"
#include<cstdio>




namespace minpp{




Character::
Character(Position  pos, Index  i, char16_t  c):
position(pos),
id_index(i),
unicode(c)
{
}




void
Character::
print(FILE*  f, bool  verbose) const
{
    if(verbose)
    {
      fprintf(f,"[");

      position.print();

      auto  txt = get_text(id_index);

      fprintf(f," %s]: ",txt? txt->id.data():"**anon**");
    }


  UTF8Chunk  chk(unicode);

  fprintf(f,"%s",chk.codes);
}


}




