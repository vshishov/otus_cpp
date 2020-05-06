#include <iostream>

static long long factorial(unsigned int n)
{
  if (n <= 1) return 1;
  return n * factorial(n -1);
}

template<typename Map>
static void print(const Map& a_map)
{
  for (auto _pair: a_map) {
    std::cout << _pair.first << " " << _pair.second << std::endl;
  }
}