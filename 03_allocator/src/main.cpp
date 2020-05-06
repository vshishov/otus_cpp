#include "allocator.h"
#include "list.h"
#include "common.h"

#include <iostream>
#include <map>

const int g_nCount = 10;

static void StdMapWithStdAllocator()
{
  std::map<int, int> _map;
  for (int i = 0; i < g_nCount; ++i) {
    _map.emplace(i, factorial(i));
  }

  print(_map);
}

static void StdMapWithCustomAllocator()
{
  std::map<int, int, std::less<int>, chunk_allocator<std::pair<int, int> > > _map;
  for (int i = 0; i < g_nCount; ++i) {
    _map.emplace(i, factorial(i));
  }

  print(_map);
}

static void CustomListWithStdAllocator()
{
  List<int> _list;
  for (int i = 0; i < g_nCount; ++i) {
    _list.Add(i);
  }

  for (auto it = _list.begin(); it != _list.end(); ++it) {
    std::cout << *it << std::endl;
  }
}

static void CustomListWithCustomAllocator()
{
  List<int,  chunk_allocator<int> > _list;
  for (int i = 0; i < g_nCount; ++i) {
    _list.Add(i);
  }

  for (auto it = _list.begin(); it != _list.end(); ++it) {
    std::cout << *it << std::endl;
  }
}

int main(int, char**)
{
  try {
    StdMapWithStdAllocator();
    StdMapWithCustomAllocator();
    CustomListWithStdAllocator();
    CustomListWithCustomAllocator();
  }
  catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
  return 0;
}