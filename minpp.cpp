#include"minpp.hpp"
#include"minpp_idtable.hpp"
#include"minpp_stream.hpp"
#include"minpp_unicode.hpp"
#include"minpp_unicode_character8.hpp"
#include<cstdlib>
#include<cstdio>
#include<cstring>




namespace minpp{


namespace{
std::string
open_file(const char*  path)
{
  std::string  buf;

  auto  f = fopen(path,"rb");

    if(f)
    {
        for(;;)
        {
          auto  c = fgetc(f);

            if(feof(f))
            {
              break;
            }


          buf.push_back(c);
        }


      fclose(f);
    }


  return std::move(buf);
}


uint16_t
get_index(Stream&  s)
{
    if(s.try_read("#fileid\""))
    {
      std::string  id;

        for(;;)
        {
          auto  c = s.get_char16();

            if(!c)
            {
              break;
            }

          else
            if(c == '\"')
            {
              break;
            }


          id.push_back(c);
        }


      return append_id(std::move(id));
    }


  return nullid;
}


}




ElementList
open(const char*  path)
{
  ElementList  ls;

  auto  src = open_file(path);

  Stream  s(src.data());

  const auto  id_index = get_index(s);

    for(;;)
    {
      auto  pos = s.get_position();

        if(s.try_read("/*"))
        {
            while(!s.try_read("*/"))
            {
              s.advance();
            }
        }

      else
        if(s.try_read("//"))
        {
            for(;;)
            {
              auto  c = s.get_char16();

                if((c == '\0') ||
                   (c == '\n'))
                {
                  break;
                }
            }
        }

      else
        if(s.try_read("#include\""))
        {
          std::string  buf = s.read_string_until('\"');

          auto  incls = open(buf.data());

            for(auto&  e: incls)
            {
              ls.emplace_back(e);
            }
        }

      else
        if(s.try_read("#include_once\""))
        {
          std::string  buf = s.read_string_until('\"');

            if(!test_id(buf))
            {
              auto  incls = open(buf.data());

                for(auto&  e: incls)
                {
                  ls.emplace_back(e);
                }
            }
        }

      else
        {
          auto  c = s.get_char16();

            if(!c)
            {
              break;
            }


          ls.emplace_back(pos,id_index,c);
        }
    }


  return std::move(ls);
}


void
print(const ElementList&  ls, FILE*  f, bool  verbose)
{
    for(auto&  e: ls)
    {
      e.print(f,verbose);

        if(verbose)
        {
          fprintf(f,"\n");
        }
    }
}




}




