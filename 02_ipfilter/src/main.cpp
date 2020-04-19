#include "version.h"
#include "ip_filter.h"

#include <iostream>

int main(int, char**)
{
  CIpPool ipPool;
  ipPool.read(std::cin); 
  ipPool.sort_reverse();  
  std::cout << ipPool << std::endl;
  std::cout << ipPool.filter(1) << std::endl;
  std::cout << ipPool.filter(46, 70) << std::endl;
  std::cout << ipPool.filter_any(46) << std::endl;
  return 0;
}