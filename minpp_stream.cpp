#include"minpp_stream.hpp"
#include"minpp_unicode.hpp"
#include"minpp.hpp"
#include<cstdio>
#include<cstring>




namespace minpp{




Stream::
Stream(const char*  p):
pointer(p),
id_index(nullidx)
{
}




void
Stream::
reset(const char*  p)
{
  position.reset();

  pointer = p;

  id_index = nullidx;
}


std::string
Stream::
read_id()
{
  std::string  id;

  auto  base = *this;

    if(try_read("#fileid\""))
    {
        for(;;)
        {
          auto  c = get_char16();

            if(!c)
            {
              printf("\'\"\'で閉じられていません\n");

              throw ErrorOnProcessStream(base);
            }

          else
            if(c == '\n')
            {
              printf("途中で改行されました\n");

              throw ErrorOnProcessStream(*this);
            }

          else
            if(c == '\"')
            {
              break;
            }


          id.push_back(c);
        }
    }


  return std::move(id);
}


Index  Stream::get_id_index() const{return id_index;}
void  Stream::change_id_index(Index  i){id_index = i;}


const std::string*
Stream::
get_id() const
{
    if(id_index != nullidx)
    {
      return &minpp::get_id(id_index);
    }


  return nullptr;
}


bool
Stream::
test() const
{
  return(*pointer);
}


bool
Stream::
test_char(char  c) const
{
  return(*pointer == c);
}


char16_t
Stream::
get_char16()
{
    if(!*pointer)
    {
      return 0;
    }


  auto  byte_number = get_utf8_byte_number(pointer);

  char16_t  c = to_char16(pointer,byte_number);

  pointer += byte_number;

    if(c == '\n')
    {
        position.line_number += 1;
      position.column_number  = 0;
    }

  else
    {
      position.column_number += 1;
    }


  return c;
}


Position
Stream::
get_position() const
{
  return position;
}


void
Stream::
advance(int  n)
{
    while(n--)
    {
      get_char16();
    }
}


bool
Stream::
try_read(const char*  s)
{
  auto  l = std::strlen(s);

    if(strncmp(pointer,s,l) == 0)
    {
      const char*  end = pointer+l;

        while(pointer != end)
        {
          get_char16();
        }


      return true;
    }


  return false;
}


void
Stream::
print(int  line_length) const
{
  position.print();

  auto  p = pointer-position.column_number;

    for(;;)
    {
      auto  c = *p++;

        if(!c || (c == '\n'))
        {
          printf("\n");

          break;
        }


      printf("%c",c);
    }


    for(int  n = 0;  n < position.column_number;  ++n)
    {
      printf(" ");
    }


    while(line_length--)
    {
      printf("~");
    }
}


}




