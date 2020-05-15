#include <iostream>

constexpr long long factorial(unsigned int n)
{
  return (n == 0 ? 1 : n * factorial(n -1) );
}

template<typename Map>
static void print(const Map& a_map)
{
  for (auto _pair: a_map) {
    std::cout << _pair.first << " " << _pair.second << std::endl;
  }
}