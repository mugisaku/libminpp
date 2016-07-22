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

            if(ferror(f))
            {
              throw ErrorOnReadFile();
            }


            if(feof(f))
            {
              break;
            }


          buf.push_back(c);
        }


      fclose(f);
    }

  else
    {
      throw ErrorOnOpenFile();
    }


  return std::move(buf);
}


uint16_t
get_index(Stream&  s)
{
  auto  base = s;

    if(s.try_read("#fileid\""))
    {
      std::string  id;

        for(;;)
        {
          auto  c = s.get_char16();

            if(!c)
            {
              printf("\'\"\'で閉じられていません\n");

              throw ErrorOnReadRange(base);
            }

          else
            if(c == '\n')
            {
              printf("途中で改行されました\n");

              throw ErrorOnReadRange(s);
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


std::string
read_string_until(Stream&  s, uint16_t  id_index, char  c)
{
  std::string  buf;

  auto  base = s;

    for(;;)
    {
      auto  cc = s.get_char16();

        if(!cc)
        {
          printf("\'%c\'で閉じられていません\n",c);

          throw ErrorOnReadRange(base,id_index);
        }

      else
        if(cc == '\n')
        {
          printf("文字列の途中で改行されました\n");

          throw ErrorOnReadRange(base,id_index);
        }

      else
        if(cc == '\\')
        {
          buf.push_back(cc);
          buf.push_back(s.get_char16());
        }

      else
        if(cc == c)
        {
          break;
        }

      else
        {
          buf.push_back(cc);
        }
    }


  return std::move(buf);
}


void
read_element_until(ElementList&  buf, Stream&  s, uint16_t  id_index, char  c)
{
  auto  base = s;

    for(;;)
    {
      auto  pos = s.get_position();

      auto  cc = s.get_char16();

        if(!cc)
        {
          printf("\'%c\'で閉じられていません\n",c);

          throw ErrorOnReadRange(base,id_index);
        }

      else
        if(cc == '\\')
        {
          buf.emplace_back(pos,id_index,cc);

          pos = s.get_position();

          cc = s.get_char16();

          buf.emplace_back(pos,id_index,cc);
        }

      else
        if(cc == c)
        {
          break;
        }

      else
        {
          buf.emplace_back(pos,id_index,cc);
        }
    }
}


bool
read_range(ElementList&  ls, Stream&  s, uint16_t  id_index, char  c)
{
    if(!s.test_char(c))
    {
      return false;
    }


  ls.emplace_back(s.get_position(),id_index,c);

  s.advance();

  read_element_until(ls,s,id_index,c);

  ls.emplace_back(s.get_position(),id_index,c);

  return true;
}


bool
read_include(ElementList&  ls, Stream&  s, uint16_t  id_index)
{
    if(!s.try_read("#include\""))
    {
      return false;
    }



  std::string  buf = read_string_until(s,id_index,'\"');

  ElementList  incls = open(buf.data(),id_index);

    for(auto&  e: incls)
    {
      ls.emplace_back(e);
    }


  return true;
}


bool
read_include_once(ElementList&  ls, Stream&  s, uint16_t  id_index)
{
    if(!s.try_read("#include_once\""))
    {
      return false;
    }


  std::string  buf = read_string_until(s,id_index,'\"');

    if(!test_id(buf))
    {
      ElementList  incls = open(buf.data(),id_index);

        for(auto&  e: incls)
        {
          ls.emplace_back(e);
        }
    }


  return true;
}


bool
read_line_comment(Stream&  s)
{
    if(!s.try_read("//"))
    {
      return false;
    }


    for(;;)
    {
      auto  c = s.get_char16();

        if((c == '\0') ||
           (c == '\n'))
        {
          break;
        }
    }


  return true;
}


bool
read_range_comment(Stream&  s, uint16_t  id_index)
{
  auto  base = s;

    if(!s.try_read("/*"))
    {
      return false;
    }


    while(!s.try_read("*/"))
    {
        if(!s.test())
        {
          printf("コメントが閉じられていません\n");

          throw ErrorOnReadRange(base,id_index);
        }


      s.advance();
    }


  return true;
}


}




ElementList
open(const char*  path, uint16_t  parent_id_index)
{
  ElementList  ls;

  std::string  src;

    try
    {
      src = open_file(path);
    }


    catch(const ErrorOnOpenFile&  e)
    {
      printf("ファイル\"%s\"を開けませんでした\n",path);

      throw;
    }


    catch(const ErrorOnReadFile&  e)
    {
      printf("ファイル\"%s\"を読み込めませんでした\n",path);

      throw;
    }



  Stream  s(src.data());

  Stream  tmps = s;

  const auto  id_index = get_index(s);

    if((       id_index != nullid) &&
       (parent_id_index != nullid))
    {
        if(id_index == parent_id_index)
        {
          printf("再帰読み込みが発生しました\n");

          throw ErrorOnInclude();
        }
    }


    try
    {
        for(;;)
        {
               if(read_range(       ls,s,id_index,'\"')){}
          else if(read_range(       ls,s,id_index,'\'')){}
          else if(read_include(     ls,s,id_index)){}
          else if(read_include_once(ls,s,id_index)){}
          else if(read_range_comment(  s,id_index)){}
          else if(read_line_comment(s)){}
          else
            {
              auto  pos = s.get_position();
              auto    c = s.get_char16();

                if(!c)
                {
                  break;
                }


              ls.emplace_back(pos,id_index,c);
            }
        }
    }


    catch(ErrorOnReadRange&  e)
    {
        if(!e.printed)
        {
            if(e.id_index != nullid)
            {
              auto&  id = get_id(e.id_index);

              printf("%s\n",id.data());
            }


          e.stream.print();

          printf("\n");

          e.printed = 1;
        }


      throw;
    }


    catch(const ErrorOnInclude&  e)
    {
      auto&  id = get_id(id_index);

      printf("%s\n",id.data());

      tmps.print();

      printf("\n");

      throw;
    }


    catch(const ErrorOnOperateFile&  e)
    {
      auto&  id = get_id(id_index);

      printf("%s\n",id.data());

      tmps.print();

      printf("\n");

      throw;
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




