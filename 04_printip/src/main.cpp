#include "print_ip.h"

#include <iostream>
#include <vector>
#include <list>
#include <tuple>

int main(int, char**)
{
  try {
    char chIp{-1};
    print_ip(chIp);

    short shIp{0};
    print_ip(shIp);
    
    int nIp{2130706433};
    print_ip(nIp);

    long lIp{8875824491850138409};
    print_ip(lIp);

    print_ip(std::string("stl string for print as is"));

    print_ip("s-ctring for print as is");

    std::vector<int> vecIp {192, 168, 1, 1};
    print_ip(vecIp);

    std::list<int> listIp {255, 255, 255, 255};
    print_ip(listIp);

    print_ip(std::make_tuple(2, 4, 8, 16));
  }
  catch (const std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
  return 0;
}