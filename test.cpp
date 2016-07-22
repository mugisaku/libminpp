#include"minpp.hpp"




using namespace minpp;


int
main(int  argc, char**  argv)
{
    if(argc == 2)
    {
      ElementList  ls;

        try
        {
          ls = open(argv[1]);
        }


        catch(...)
        {
          exit(-1);
        }


      print(ls);
    }


  return 0;
}




