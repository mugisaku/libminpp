#include"minpp.hpp"




using namespace minpp;


int
main(int  argc, char**  argv)
{
    if(argc == 2)
    {
      auto  ls = open(argv[1]);

      print(ls);
    }


  return 0;
}




