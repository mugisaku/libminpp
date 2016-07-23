#include"minpp.hpp"
#include<vector>




namespace minpp{


namespace{


struct
Text
{
  std::string  id;

  char*  pointer;

  Text(std::string&&  id_, char*  p):
  id(std::move(id_)),
  pointer(p){}

};


std::vector<Text>
table;


char*
open_file(const char*  path)
{
  auto  f = fopen(path,"rb");

    if(f)
    {
      size_t  size = 0;

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


          size += 1;
        }


        if(fseek(f,0,SEEK_SET) != 0)
        {
          throw ErrorOnReadFile();
        }


      char*      base = static_cast<char*>(malloc(size+1));
      char*  p = base                                     ;

        while(size--)
        {
          *p++ = fgetc(f);
        }


      *p = 0;

      return base;
    }

  else
    {
      throw ErrorOnOpenFile();
    }


  return nullptr;
}


Index
push_id(std::string&&  id, char*  p)
{
  Index  i = 0;

    for(auto&  text: table)
    {
        if(text.id == id)
        {
          return i;
        }


      ++i;
    }


  table.emplace_back(std::move(id),p);

  return i;
}


}


bool
test_id(const std::string&  id)
{
    for(auto&  txt: table)
    {
        if(txt.id == id)
        {
          return true;
        }
    }


  return false;
}


const std::string&
get_id(Index  i)
{
  return table[i].id;
}


const char*
get_text(Index  i)
{
  return table[i].pointer;
}


Stream
create_stream_from_file(const char*  path)
{
  auto  p = open_file(path);

  Stream  s(p);

  auto  id = s.read_id();

    if(id.size())
    {
      s.change_id_index(push_id(std::move(id),p));
    }

  else
    {
      s.change_id_index(nullidx);
    }


  return s;
}


}




