#include"minpp_utf8chunk.hpp"


namespace minpp{




UTF8Chunk::
UTF8Chunk(char16_t  c)
{
  *this = c;
}




UTF8Chunk&
UTF8Chunk::
operator=(char16_t  c)
{
    if(c <= 0x7F)
    {
      codes[0] = c;
      codes[1] = 0;
    }

  else
    if((c >= 0x0080) &&
       (c <= 0x07FF))
    {
      codes[0] = (0b11000000|(c>>6));
      codes[1] = (0b10000000|(c&0b111111));
      codes[2] = 0;
    }

  else
    if((c >= 0x0800) &&
       (c <= 0xFFFF))
    {
      codes[0] = (0b11100000|(c>>12));
      codes[1] = (0b10000000|((c>>6)&0b111111));
      codes[2] = (0b10000000|((c   )&0b111111));
      codes[3] = 0;
    }


  return *this;
}


}




