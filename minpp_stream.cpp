#include"minpp_stream.hpp"
#include"minpp_unicode.hpp"
#include<cstdio>
#include<cstring>




namespace minpp{




Stream::
Stream(const char*  p):
pointer(p)
{
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




