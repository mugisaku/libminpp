#include"minpp.hpp"
#include"minpp_stream.hpp"
#include"minpp_unicode.hpp"
#include"minpp_utf8chunk.hpp"
#include<cstdlib>
#include<cstdio>
#include<cstring>




namespace minpp{


namespace{
std::string
read_string_until(Stream&  s, char  c)
{
  std::string  buf;

  auto  base = s;

    for(;;)
    {
      auto  cc = s.get_char16();

        if(!cc)
        {
          printf("\'%c\'で閉じられていません\n",c);

          throw ErrorOnProcessStream(base);
        }

      else
        if(cc == '\n')
        {
          printf("文字列の途中で改行されました\n");

          throw ErrorOnProcessStream(base);
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
read_element_until(ElementList&  buf, Stream&  s, char  c)
{
  auto  base = s;

  auto  id_index = s.get_id_index();

    for(;;)
    {
      auto  pos = s.get_position();

      auto  cc = s.get_char16();

        if(!cc)
        {
          printf("\'%c\'で閉じられていません\n",c);

          throw ErrorOnProcessStream(base);
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
read_range(ElementList&  ls, Stream&  s, char  c)
{
    if(!s.test_char(c))
    {
      return false;
    }


  auto  id_index = s.get_id_index();

  ls.emplace_back(s.get_position(),id_index,c);

  s.advance();

  read_element_until(ls,s,c);

  ls.emplace_back(s.get_position(),id_index,c);

  return true;
}


bool
read_include(ElementList&  ls, Stream&  s)
{
    if(!s.try_read("#include\""))
    {
      return false;
    }



  std::string  buf = read_string_until(s,'\"');

  ElementList  incls = open(buf.data(),s.get_id_index());

    for(auto&  e: incls)
    {
      ls.emplace_back(e);
    }


  return true;
}


bool
read_include_once(ElementList&  ls, Stream&  s)
{
    if(!s.try_read("#include_once\""))
    {
      return false;
    }


  std::string  buf = read_string_until(s,'\"');

    if(!test_id(buf))
    {
      ElementList  incls = open(buf.data(),s.get_id_index());

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
read_range_comment(Stream&  s)
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

          throw ErrorOnProcessStream(base);
        }


      s.advance();
    }


  return true;
}


}




ElementList
open(const char*  path, Index  parent_id_index)
{
  ElementList  ls;

  Stream  s;

    try
    {
      s = create_stream_from_file(path);
    }


    catch(ErrorOnProcessStream&  e)
    {
      throw;
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



  Stream  tmps = s;

    if((s.get_id_index() != nullidx) &&
       ( parent_id_index != nullidx))
    {
        if(s.get_id_index() == parent_id_index)
        {
          printf("再帰読み込みが発生しました\n");

          throw ErrorOnInclude();
        }
    }


    try
    {
        for(;;)
        {
               if(read_range(       ls,s,'\"')){}
          else if(read_range(       ls,s,'\'')){}
          else if(read_include(     ls,s)){}
          else if(read_include_once(ls,s)){}
          else if(read_range_comment(  s)){}
          else if(read_line_comment(s)){}
          else
            {
              auto  pos = s.get_position();
              auto    c = s.get_char16();

                if(!c)
                {
                  break;
                }


              ls.emplace_back(pos,s.get_id_index(),c);
            }
        }
    }


    catch(ErrorOnProcessStream&  e)
    {
        if(!e.printed)
        {
          auto  id = e.stream.get_id();

            if(id)
            {
              printf("%s\n",id->data());
            }


          e.stream.print();

          printf("\n");

          e.printed = 1;
        }


      throw;
    }


    catch(const ErrorOnInclude&  e)
    {
      auto  id = s.get_id();

        if(id)
        {
          printf("%s\n",id->data());
        }


      tmps.print();

      printf("\n");

      throw;
    }


    catch(const ErrorOnOperateFile&  e)
    {
      auto  id = s.get_id();

        if(id)
        {
          printf("%s\n",id->data());
        }


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




