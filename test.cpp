#include"minpp.hpp"




using namespace minpp;


int
main(int  argc, char**  argv)
{
    if(argc == 2)
    {
      String  str;

        try
        {
          str.open(argv[1]);
        }


        catch(...)
        {
          exit(-1);
        }


      str.print(stdout);

      printf("\n");
    }


  return 0;
}




