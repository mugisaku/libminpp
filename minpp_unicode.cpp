#include"minpp_unicode.hpp"
#include<cstdio>




namespace minpp{




size_t
u16strlen(const char16_t*  str)
{
  size_t  len = 0;

    while(*str++)
    {
      ++len;
    }


  return len;
}


size_t
get_utf8_byte_number(const char*  s)
{
  const int  c = *(const unsigned char*)s;

       if(!(c>>7)          ){return 1;}
  else if( (c>>4) == 0b1110){return 3;}
  else if( (c>>5) == 0b110 ){return 2;}
  else if( (c>>6) == 0b10  ){return 1;}


  return 0;
}


size_t
get_utf8_length(const char*  s)
{
  size_t  length = 0;

    for(;;)
    {
      const size_t  byte_number = get_utf8_byte_number(s);

        if(!byte_number)
        {
          break;
        }


      ++length;

      s += byte_number;
    }


  return length;
}


char16_t
to_char16(const char*  s, size_t  byte_number)
{
    switch(byte_number)
    {
      case(1): return ((s[0]             )                                    );break;
      case(2): return ((s[0]&0b11111)<< 6)|((s[1]&0b111111)                   );break;
      case(3): return ((s[0]&0b01111)<<12)|((s[1]&0b111111)<<6)|(s[2]&0b111111);break;
    }


  return 0;
}


}




