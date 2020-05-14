#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <type_traits>

const char OCTET_SEPARATOR = '.';

template<
  typename T, 
  typename = std::enable_if_t<std::is_integral<T>::value> 
>
void print_ip(T num){
  int nCountByte = static_cast<int>(sizeof(T));
  for (int i = nCountByte - 1; i >= 0; --i) {    
    std::cout << (num >> ((i) * 8) & 0xFF);
    if (i > 0) {
       std::cout << OCTET_SEPARATOR;
    }
  }
  std::cout << std::endl;
}

template<typename>
struct is_vector_or_list : std::false_type {};

template<typename T, typename... Types>
struct is_vector_or_list<std::vector<T, Types...>> : std::true_type {};

template<typename T, typename... Types>
struct is_vector_or_list<std::list<T, Types...>> : std::true_type {};

template<
  typename T, 
  typename = std::enable_if_t<is_vector_or_list<T>::value> 
>
void print_ip(const T& container){
  for (auto it = container.begin(); it != container.end(); ++it) {
    if (it != container.begin())
      std::cout << OCTET_SEPARATOR;
    
    std::cout << *it;
  }
  std::cout << std::endl;
}

/**
 * 
 */
template<class Tuple, std::size_t N>
struct TuplePrinter {
  static void print(const Tuple& t) 
  {
    static_assert(std::is_same<decltype(std::get<N-1>(t)), decltype(std::get<N-2>(t))>::value, "Types in a tuple are different!");
    TuplePrinter<Tuple, N-1>::print(t);
    std::cout << OCTET_SEPARATOR << std::get<N-1>(t);
  }
};
 
template<class Tuple>
struct TuplePrinter<Tuple, 1> {
  static void print(const Tuple& t) 
  {
    std::cout << std::get<0>(t);
  }
};
 
/**
 * @brief print_ip
 * @param value - std::string
 * 
 * @details Prints the contents of a string
 */
template<typename... Args, std::enable_if_t<sizeof...(Args) != 0, int> = 0>
void print_ip(const std::tuple<Args...>& t)
{
  TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
  std::cout << std::endl;
}

/**
 * @brief print_ip
 * @param value - std::string
 * 
 * @details Prints the contents of a string
 */
void print_ip(const std::string& value){
  std::cout << value << std::endl;
}

